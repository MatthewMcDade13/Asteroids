#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "ResourceHolder.h"
#include "StateManager.h"
#include "GameState.h"
#include "PausedState.h"

using namespace pure; using namespace sf;

PausedState::PausedState(StateManager* manager, ResourceHolder* resources)
	:State(manager),
	m_resources(resources)
{
	m_bTransparent = true;
}


PausedState::~PausedState()
{
}

void PausedState::update(float deltaTime)
{
}

void PausedState::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_pauseText);
}

void PausedState::onCreate()
{
	const Vector2u winSize = m_stateManager->getWindow().getSize();

	if (const Font* pauseFont = m_resources->fontManager.get("ARCADE_N.TTF"))
	{
		m_pauseText.setFont(*pauseFont);
		m_pauseText.setCharacterSize(69);
		m_pauseText.setString("PAUSED");

		const FloatRect textSize = m_pauseText.getLocalBounds();

		m_pauseText.setOrigin(textSize.width / 2, textSize.height / 2);
		m_pauseText.setPosition((float)winSize.x / 2.f, (float)winSize.y / 2.f);
	}

	m_background.setFillColor(Color(0, 0, 0, 120));
	m_background.setSize(Vector2f((float)winSize.x, (float)winSize.y));
}

void PausedState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Escape)
		{
			m_stateManager->pushState(GameState::Playing);
		}
	}
}
