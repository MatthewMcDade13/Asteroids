#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Random.h"
#include "StateManager.h"
#include "GameState.h"
#include "PlayState.h"
#include "DebugLog.h"

using namespace pure; using namespace sf; using namespace std;

PlayState::PlayState(StateManager* manager, ResourceHolder* resources):
	State(manager),
	m_resources(resources)
{
}

PlayState::~PlayState()
{
}

void PlayState::update(float deltaTime)
{
	m_player.handleLiveInput(deltaTime);

	m_player.getShip().update(deltaTime);
	clampEntity(m_player.getShip());


	for (auto& ast : m_asteroids)
	{
		ast->update(deltaTime);
		clampEntity(*ast);
	}
}

void PlayState::draw(sf::RenderWindow& window)
{
	window.draw(m_player.getShip());
	for (auto& ast : m_asteroids)
	{
		window.draw(*ast);
	}
}

void PlayState::onCreate()
{
	const int winWidth = getWindow().getSize().x;
	const int winHeight = getWindow().getSize().y;

	m_player.setupKeybinds();
	m_player.spawn(Vector2f(winWidth / 2.f, winHeight / 2.f));

	const Random rand;
	const int astroidCount = 15;

	m_asteroids.reserve(astroidCount);
	for (int i = 0; i < astroidCount; i++)
	{
		m_asteroids.emplace_back(make_unique<Asteroid>());		

		m_asteroids.back()->spawnAt(Vector2f(rand((float)winWidth), rand((float)winHeight)), 30);

		const float asteroidSpeed = rand(500.f);

		m_asteroids.back()->setSpeed(asteroidSpeed);
		m_asteroids.back()->setVelocity(Vector2f(asteroidSpeed * rand(-1.f, 1.f), asteroidSpeed * rand(-1.f, 1.f)));
	}
}

//void PlayState::clampEntity(SpaceEntity& entity)
//{
//	const Vector2f offset = entity.getMidOffset();
//
//	if (entity.getPosition().x + offset.x < 0)
//	{
//		entity.setPosition(getWindow().getSize().x + offset.x, entity.getPosition().y);
//	}
//	else if (entity.getPosition().x - offset.x > getWindow().getSize().x)
//	{
//		entity.setPosition(-(offset.x), entity.getPosition().y);
//	}
//	else if (entity.getPosition().y + offset.y < 0)
//	{
//		entity.setPosition(entity.getPosition().x, getWindow().getSize().y + offset.y);
//	}
//	else if (entity.getPosition().y - offset.y > getWindow().getSize().y)
//	{
//		entity.setPosition(entity.getPosition().x, -(offset.y));
//	}
//}

const sf::RenderWindow& PlayState::getWindow() const
{
	return m_stateManager->getWindow();
}

void PlayState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Space)
		{
			m_stateManager->pushState(GameState::Paused);
		}
		else if (event.key.code == Keyboard::Return)
		{
			Asteroid* ass = m_asteroids[0].get();
			ass->setVelocity(-(ass->getVelocity()));
		}
	}
}

