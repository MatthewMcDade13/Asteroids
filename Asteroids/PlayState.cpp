#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Random.h"
#include <utility>
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

	for (auto& a : getAsteroids())
	{
		Asteroid* ast = a.first;
		ast->update(deltaTime);
		clampEntity(*ast);
	}
}

void PlayState::draw(sf::RenderWindow& window)
{
	window.draw(m_player.getShip());

	for (auto& a : getAsteroids())
	{
		Asteroid* ast = a.first;
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

	for (int i = 0; i < astroidCount; i++)
	{
		Asteroid* ast = m_asteroidPool.create(Vector2f(rand((float)winWidth), rand((float)winHeight)), 30);

		const float asteroidSpeed = rand(500.f);

		ast->setSpeed(asteroidSpeed);
		ast->setVelocity(Vector2f(asteroidSpeed * rand(-1.f, 1.f), asteroidSpeed * rand(-1.f, 1.f)));
	}
}


const sf::RenderWindow& PlayState::getWindow() const
{
	return m_stateManager->getWindow();
}

const std::vector<std::pair<Asteroid*, int>> PlayState::getAsteroids() const
{
	return m_asteroidPool.getActiveAsteroids();
}

void PlayState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Space)
		{
			m_stateManager->pushState(GameState::Paused);
		}
	}
}

