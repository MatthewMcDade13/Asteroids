#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "GameState.h"
#include "ResourceHolder.h"
#include "StateManager.h"
#include "GameOverState.h"

using namespace pure;
using namespace sf;

GameOverState::GameOverState(StateManager* manager, ResourceHolder* resources):
	State(manager),
	m_resources(resources)
{
	m_bTransparent = true;
	m_bTranscendant = true;
}


GameOverState::~GameOverState()
{
}

void GameOverState::update(float deltaTime)
{
}

void GameOverState::draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	window.draw(m_gameOverText);
	window.draw(m_resumeText);
}

void GameOverState::onCreate()
{
	const Vector2u winSize = m_stateManager->getWindow().getSize();

	if (const Font* gameFont = m_resources->fontManager.get("ARCADE_N.TTF"))
	{
		m_gameOverText.setFont(*gameFont);
		m_gameOverText.setCharacterSize(69);
		m_resumeText.setFont(*gameFont);
		m_resumeText.setCharacterSize(36);

		m_gameOverText.setString("GAME OVER");
		m_resumeText.setString("Press Enter to play again");

		const FloatRect goSize = m_gameOverText.getLocalBounds();
		const FloatRect resSize = m_resumeText.getLocalBounds();

		m_gameOverText.setOrigin(goSize.width / 2, goSize.height / 2);
		m_resumeText.setOrigin(resSize.width / 2, resSize.height / 2);

		m_gameOverText.setPosition((float)winSize.x / 2.f, ((float)winSize.y / 2.f) - 150.f);
		m_resumeText.setPosition((float)winSize.x / 2.f, ((float)winSize.y / 2.f) + 150.f);
	}

	m_background.setFillColor(Color(0, 0, 0, 120));
	m_background.setSize(Vector2f((float)winSize.x, (float)winSize.y));
}

void GameOverState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Return)
		{
			m_stateManager->pushState(GameState::Playing);
		}
	}
}
