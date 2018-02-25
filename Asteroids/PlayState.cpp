#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Random.h"
#include <utility>
#include <assert.h>
#include "Context.h"
#include "Constants.h"
#include "ResourceHolder.h"
#include "PausedState.h"
#include "GameAudio.h"
#include "StateManager.h"
#include "GameOverState.h"
#include "ResourcePaths.h"
#include "GameState.h"
#include "PlayState.h"
#include "DebugLog.h"

using namespace pure; using namespace sf; using namespace std;

PlayState::PlayState(StateManager* manager, ::Context* ctx):
	State(manager),
	m_player(&m_bulletPool, ctx->audio),
	m_asteroidPool(255),
	m_bulletPool(100),
	m_ctx(ctx),
	m_playerScore(0),
	m_numStartAsteroids(0),
	m_playerLives(m_playerStartLives)
{
	m_explosions.reserve(10);
}

PlayState::~PlayState()
{
}

void PlayState::update(float deltaTime)
{

	if (!canPlayerRespawn() && m_stateManager->getCurrentState<PlayState>())
	{
		stopAndResetMusic();
		m_stateManager->pushState(GameState::GameOver);
	}
		

	if (getAsteroids().size() == 0)
	{
		m_numStartAsteroids += 2;
		const Random rand;
		const Vector2f winSize((float)getWindow().getSize().x, (float)getWindow().getSize().y);

		for (int i = 0; i < m_numStartAsteroids; i++)
		{
			Asteroid* ast = m_asteroidPool.create();

			spawnAsteroid(ast);
		}
	}

	for (int i = (int)m_explosions.size() - 1; i >= 0; i--)
	{
		Explosion& explosion = m_explosions[i];

		if (explosion.isDone())
			m_explosions.erase(m_explosions.begin() + i);
		else
			explosion.update(deltaTime);
	}

	if (m_player.isAlive())
	{
		m_player.handleLiveInput(deltaTime);

		m_player.getShip().update(deltaTime);
		clampEntity(m_player.getShip());
	}
	

	for (auto& a : getAsteroids())
	{
		Asteroid* ast = a;
		ast->update(deltaTime);
		clampEntity(*ast);
	}

	const vector<PBullet*>& bullets = getBullets();

	for (int i = (int)bullets.size() - 1; i >= 0; i--)
	{
		Bullet* bullet = bullets[i];
		bullet->update(deltaTime);

		if (bullet->isExpired())
		{
			m_bulletPool.destroy(i);
			continue;
		}

		clampEntity(*bullet);
	}

	const vector<PAsteroid*>& asteroids = getAsteroids();

	for (int i = (int)asteroids.size() - 1; i >= 0; i--)
	{
		Asteroid* ast = asteroids[i];
		for (int j = (int)bullets.size() - 1; j >= 0; j--)
		{
			Bullet* bullet = bullets[j];
			if (bullet->detectCollision(ast))
			{
				m_bulletPool.destroy(j);
				destroyAsteroid(static_cast<PAsteroid*>(ast), i);
				break;
			}
		}

		if (!m_player.isAlive()) continue;

		if (ast->detectCollision(&m_player.getShip()))
		{
			m_player.die();
			m_explosions.emplace_back();
			m_explosions.back().spawnAt(m_player.getShip().getPosition());
			m_playerLives--;
			updateLivesDisplay();

			if (ast->getSize() == Asteroid::Size::Small)
				destroyAsteroid(static_cast<PAsteroid*>(ast), i);
		}
	}

}

void PlayState::draw(sf::RenderWindow& window)
{
	window.draw(m_player.getShip());

	for (Asteroid* ast : getAsteroids())
	{
		window.draw(*ast);
	}

	for (Bullet* bullet : getBullets())
	{
		window.draw(*bullet);
	}

	for (Explosion& ex : m_explosions)
	{
		window.draw(ex);
	}

	window.draw(m_scoreText);
	window.draw(m_livesText);
}

void PlayState::onCreate()
{
	m_player.setupKeybinds();
	m_ctx->audio->gameplayMusic.setLoop(true);

	float winSizeX = (float)getWindow().getSize().x;

	const string fontPath = getResourcePath(Resource::Font_Arcade);

	{
		m_scoreText.setFont(*m_ctx->resources->fontManager.get(fontPath));
		m_scoreText.setCharacterSize(24);
		updateScoreDisplay(); 
		const FloatRect textSize = m_scoreText.getLocalBounds();
		m_scoreText.setOrigin(textSize.width / 2.f, textSize.height / 2.f);
		m_scoreText.setPosition(winSizeX / 4.f, 15.f);
	}

	{
		m_livesText.setFont(*m_ctx->resources->fontManager.get(fontPath));
		m_livesText.setCharacterSize(24);
		updateLivesDisplay();
		const FloatRect textSize = m_livesText.getLocalBounds();
		m_livesText.setOrigin(textSize.width / 2.f, textSize.height / 2.f);
		m_livesText.setPosition(winSizeX * 0.75f, 15.f);
	}
}


const sf::RenderWindow& PlayState::getWindow() const
{
	return m_stateManager->getWindow();
}

const std::vector<PAsteroid*>& PlayState::getAsteroids() const
{
	return m_asteroidPool.getActiveObjects();
}

const std::vector<PBullet*>& PlayState::getBullets() const
{

	return m_bulletPool.getActiveObjects();
}

bool PlayState::canPlayerRespawn() const
{
	return m_playerLives > 0;
}

void PlayState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Escape)
		{
			m_stateManager->pushState(GameState::Paused);
		}
		if (event.key.code == Keyboard::Return)
		{
			if (!m_player.isAlive() && canPlayerRespawn())
			{
				const Vector2u winSize = getWindow().getSize();
				m_player.spawn(Vector2f((float)winSize.x / 2.f, (float)winSize.y / 2.f));
			}
		}	

		if (event.key.code == Keyboard::R)
			reset();
	}
}

void PlayState::onActivate()
{
	if (!m_stateManager->getCurrentState<PausedState>())
		m_ctx->audio->gameplayMusic.play();

	if (m_stateManager->getCurrentState<GameOverState>())
		reset();

	if (!m_player.isAlive())
	{
		const Vector2u winSize = getWindow().getSize();
		m_player.spawn(Vector2f(winSize.x / 2.f, winSize.y / 2.f));
	}
}

void PlayState::destroyAsteroid(PAsteroid* ast, int astIndx)
{
	Asteroid::Size size = ast->getSize();

	calcPlayerScore(size);
	updateScoreDisplay();

	if (m_playerScore % 10000 == 0)
	{
		m_playerLives++;
		updateLivesDisplay();
	}

	--size;
	const Random rand;

	if (size != Asteroid::Size::Microscopic)
	{
		const int numAsteroids = size == Asteroid::Size::Medium ? 2 : 4;

		for (int i = 0; i < numAsteroids; i++)
		{
			Asteroid* newAst = m_asteroidPool.create();
			newAst->spawnAt(ast->getPosition(), size);
		}
	}

	m_ctx->audio->explodeSound.play();
	m_explosions.emplace_back();
	m_explosions.back().spawnAt(ast->getPosition());
	
	if (astIndx >= 0)
	{
		m_asteroidPool.destroy(astIndx);
	}
	else
	{
		m_asteroidPool.destroy(ast);
	}
}

void PlayState::spawnAsteroid(Asteroid * ast)
{
	// Spawn asteroid somewhere on the edge of the screen
	const Random rand;
	const Vector2f winSize((float)getWindow().getSize().x, (float)getWindow().getSize().y);

	const pair<float, float> smallRangeX = { 0.f, (float)winSize.x * .25f };
	const pair<float, float> largeRangeX = { (float)winSize.x * .75f, winSize.x };
	const pair<float, float> smallRangeY = { 0.f, (float)winSize.y * .25f };
	const pair<float, float> largeRangeY = { (float)winSize.y * .75f, winSize.y };

	const pair<float, float> xRangeSize = { (smallRangeX.second - smallRangeX.first), (largeRangeX.second - largeRangeX.first) };
	const pair<float, float> yRangeSize = { (smallRangeY.second - smallRangeY.first), (largeRangeY.second - largeRangeY.first) };

	const float xRangeSum = xRangeSize.first + xRangeSize.second;
	const float yRangeSum = yRangeSize.first + yRangeSize.second;

	float randX = rand(xRangeSum);
	if (randX < xRangeSize.first)
		randX += (smallRangeX.first);
	else
		randX += largeRangeX.first - xRangeSize.first;

	float randY = rand(yRangeSum);
	if (randY < (yRangeSize.first))
		randY += (smallRangeY.first);
	else
		randY += largeRangeY.first - yRangeSize.first;

	ast->spawnAt(Vector2f(randX, randY), Asteroid::Size::Large);
}

void PlayState::calcPlayerScore(Asteroid::Size astSize)
{
	// Scores taken from Atari Asteroid Manual found here
	// https://atariage.com/manual_html_page.php?SoftwareID=828

	switch (astSize)
	{
		case Asteroid::Size::Large:  m_playerScore += 20;  break;
		case Asteroid::Size::Medium: m_playerScore += 50;  break;
		case Asteroid::Size::Small:  m_playerScore += 100; break;
	}
}

void PlayState::stopAndResetMusic()
{
	m_ctx->audio->gameplayMusic.pause();
	m_ctx->audio->gameplayMusic.setPlayingOffset(sf::Time::Zero);
}

void PlayState::updateLivesDisplay()
{
	m_livesText.setString("Lives: "s + to_string(m_playerLives));
}

void PlayState::updateScoreDisplay()
{
	m_scoreText.setString("Score: "s + to_string(m_playerScore));
}

void PlayState::reset()
{
	m_numStartAsteroids = 0;
	m_playerLives = m_playerStartLives;
	m_playerScore = 0;

	updateScoreDisplay();
	updateLivesDisplay();

	m_bulletPool.reset();
	m_asteroidPool.reset();
	m_player.reset();
}

