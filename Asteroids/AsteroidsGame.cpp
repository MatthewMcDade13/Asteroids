#include "stdafx.h"
#include <random>
#include "StateManager.h"
#include "ResourceHolder.h"
#include "PlayState.h"
#include "PausedState.h"
#include "GameOverState.h"
#include "GameState.h"
#include "DebugLog.h"
#include "AsteroidsGame.h"
#include "ResourcePaths.h"

using namespace sf;
using namespace std;
using namespace pure;

AsteroidsGame::AsteroidsGame():
	m_stateManager(m_window)
{
	m_audio.explodeSound.setBuffer(*m_resources.soundManager.get(getResourcePath(Resource::Sound_Explode)));
	m_audio.lazerSound.setBuffer(*m_resources.soundManager.get(getResourcePath(Resource::Sound_Lazer)));
	m_audio.gameplayMusic.openFromFile(getResourcePath(Resource::Music_Playing));

	m_ctx.audio = &m_audio;
	m_ctx.resources = &m_resources;
}


AsteroidsGame::~AsteroidsGame()
{
}

void AsteroidsGame::onGameStart()
{
	m_stateManager.registerState(GameState::Playing, [this](StateManager* manager) {
		return make_unique<PlayState>(manager, &m_ctx);
	});

	m_stateManager.registerState(GameState::Paused, [this](StateManager* manager) {
		return make_unique<PausedState>(manager, &m_ctx);
	});

	m_stateManager.registerState(GameState::GameOver, [this](StateManager* manager) {
		return make_unique<GameOverState>(manager, &m_resources);
	});

	m_stateManager.pushState(GameState::Playing);
	m_resources.fontManager.load(getResourcePath(Resource::Font_Arcade));

	m_window.setVerticalSyncEnabled(true);
	//setFrameTime(75); // set frametime(fps) for fixed update step to be the same as monitor refresh rate
	//setFPS(true);
	
}

void AsteroidsGame::draw()
{
	m_stateManager.draw();
}

void AsteroidsGame::update(float deltaTime)
{
	m_stateManager.update(deltaTime);
}

void AsteroidsGame::handleInput(const sf::Event & event)
{
	m_stateManager.handleInput(event);
}
