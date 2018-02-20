#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Random.h"
#include <utility>
#include <assert.h>
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
	m_numStartAsteroids(0)
{
}

PlayState::~PlayState()
{
}

void PlayState::update(float deltaTime)
{

	if (!m_player.canRespawn())
	{
		reset();
		m_stateManager->pushState(GameState::GameOver);
		return;
	}


	if (getAsteroids().size() == 0)
	{
		m_numStartAsteroids += 2;
		const Random rand;
		const Vector2u winSize = getWindow().getSize();

		for (int i = 0; i < m_numStartAsteroids; i++)
		{
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

	for (int i = (int)bullets.size() - 1; i >= 0; i--)
	{
		Bullet* bullet = bullets[i];

		for (int j = 0; j < (int)getAsteroids().size(); j++)
		{
			Asteroid* ast = getAsteroids()[j];
			if (bullet->detectCollision(ast))
			{
				m_bulletPool.destroy(i);
				destroyAsteroid(static_cast<PAsteroid*>(ast), j);
				break;
			}
		}
	}

	if (!m_player.isAlive()) return;
	for (Asteroid* ast : getAsteroids())
	{
		if (ast->detectCollision(&m_player.getShip()))
		{
			m_player.die();
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
}

void PlayState::onCreate()
{
	m_player.setupKeybinds();
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
			if (!m_player.isAlive() && m_player.canRespawn())
			{
				const Vector2u winSize = getWindow().getSize();
				m_player.spawn(Vector2f(winSize.x / 2, winSize.y / 2));
			}
		}	

		if (event.key.code == Keyboard::R)
			reset();
	}
}

void PlayState::onActivate()
{
	if (!m_player.isAlive())
	{
		const Vector2u winSize = getWindow().getSize();
		m_player.spawn(Vector2f(winSize.x / 2.f, winSize.y / 2.f));
	}

	if (m_stateManager->getCurrentState<GameOverState>())
		m_asteroidPool.reset();
}

void PlayState::destroyAsteroid(PAsteroid* ast, int astIndx)
{
	Asteroid::Size size = ast->getSize();
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

void PlayState::reset()
{
	m_numStartAsteroids = 0;
	m_bulletPool.reset();
	m_player.reset();
}

