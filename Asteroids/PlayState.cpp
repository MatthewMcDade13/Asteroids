#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Random.h"
#include <utility>
#include <assert.h>
#include "Constants.h"
#include "ResourceHolder.h"
#include "StateManager.h"
#include "GameOverState.h"
#include "GameState.h"
#include "PlayState.h"
#include "DebugLog.h"

using namespace pure; using namespace sf; using namespace std;

PlayState::PlayState(StateManager* manager, ResourceHolder* resources):
	State(manager),
	m_player(&m_bulletPool),
	m_asteroidPool(255),
	m_bulletPool(100),
	m_resources(resources),
	m_numStartAsteroids(0),
	m_playerLives(m_playerStartLives)
{
}

PlayState::~PlayState()
{
}

void PlayState::update(float deltaTime)
{

	if (!canPlayerRespawn())
		m_stateManager->pushState(GameState::GameOver);


	if (getAsteroids().size() == 0)
	{
		m_numStartAsteroids += 2;
		const Random rand;
		const Vector2f winSize((float)getWindow().getSize().x, (float)getWindow().getSize().y);

		for (int i = 0; i < m_numStartAsteroids; i++)
		{
			// TODO: Make asteroids spawn on outer rim of screen or near edge of screen.
			Asteroid* ast = m_asteroidPool.create();
			ast->spawnAt(Vector2f(rand((float)winSize.x), rand((float)winSize.y)), Asteroid::Size::Large);
		}
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

	window.draw(m_scoreText);
	window.draw(m_livesText);
}

void PlayState::onCreate()
{
	m_player.setupKeybinds();
	float winSizeX = (float)getWindow().getSize().x;

	{
		m_scoreText.setFont(*m_resources->fontManager.get("ARCADE_N.TTF"));
		m_scoreText.setCharacterSize(24);
		updateScoreDisplay(); // initially 0
		const FloatRect textSize = m_scoreText.getLocalBounds();
		m_scoreText.setOrigin(textSize.width / 2.f, textSize.height / 2.f);
		m_scoreText.setPosition(winSizeX / 4.f, 15.f);
	}

	{
		m_livesText.setFont(*m_resources->fontManager.get("ARCADE_N.TTF"));
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
	
	if (astIndx >= 0)
	{
		m_asteroidPool.destroy(astIndx);
	}
	else
	{
		m_asteroidPool.destroy(ast);
	}
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

