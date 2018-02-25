#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "ResourceHolder.h"
#include "ResourcePaths.h"
#include "Context.h"
#include "GameAudio.h"
#include "StateManager.h"
#include "GameState.h"
#include "PausedState.h"

using namespace pure; 
using namespace sf;
using namespace std;

PausedState::PausedState(StateManager* manager, ::Context* ctx)
	:State(manager),
	m_ctx(ctx)
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
	window.draw(m_settingsText);
}

void PausedState::updateSettingsText()
{
	const bool isMusicMuted = m_ctx->audio->isMusicMuted();
	const bool isSEMuted = m_ctx->audio->areEffectsMuted();

	string settingsStr = "M - Toggle Music   :: "s + (isMusicMuted ? "OFF"s : "ON"s) + "\n"s;
	settingsStr += "N - Toggle Effects :: "s + (isSEMuted ? "OFF"s : "ON"s);

	m_settingsText.setString(settingsStr);

	const FloatRect textSize = m_settingsText.getLocalBounds();
	const Vector2u winSize = m_stateManager->getWindow().getSize();

	m_settingsText.setOrigin(textSize.width / 2, textSize.height / 2);
	m_settingsText.setPosition((float)winSize.x / 2.f, (float)winSize.y * .25f);
	//m_settingsText.setPosition((float)winSize.x / 2.f, (float)winSize.y / 2.f);
}

void PausedState::onCreate()
{
	const Vector2u winSize = m_stateManager->getWindow().getSize();
	const string fontPath = getResourcePath(Resource::Font_Arcade);
	if (const Font* pauseFont = m_ctx->resources->fontManager.get(fontPath))
	{
		m_pauseText.setFont(*pauseFont);
		m_pauseText.setCharacterSize(69);
		m_pauseText.setString("PAUSED");

		const FloatRect textSize = m_pauseText.getLocalBounds();

		m_pauseText.setOrigin(textSize.width / 2, textSize.height / 2);
		m_pauseText.setPosition((float)winSize.x / 2.f, (float)winSize.y / 2.f);
	}

	if (const Font* settingsFont = m_ctx->resources->fontManager.get(fontPath))
	{
		m_settingsText.setFont(*settingsFont);
		m_settingsText.setCharacterSize(12);
		m_settingsText.setString("");
	}

	m_background.setFillColor(Color(0, 0, 0, 120));
	m_background.setSize(Vector2f((float)winSize.x, (float)winSize.y));
}

void PausedState::handleInput(const sf::Event& event)
{
	if (event.type == Event::KeyReleased)
	{
		switch(event.key.code)
		{
			case Keyboard::Escape:
				m_stateManager->pushState(GameState::Playing);
				break;
			case Keyboard::M:

				if (m_ctx->audio->isMusicMuted())
					m_ctx->audio->unMuteMusic();
				else
					m_ctx->audio->muteMusic();

				updateSettingsText();
				break;
			case Keyboard::N:
				if (m_ctx->audio->areEffectsMuted())
					m_ctx->audio->unMuteSoundEffects();
				else
					m_ctx->audio->muteSoundEffects();

				updateSettingsText();
				break;
		}
	}
}

void PausedState::onActivate()
{
	updateSettingsText();
}
