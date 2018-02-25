#pragma once

#include "StateManager.h"
#include "AsteroidPlayer.h"
#include "Context.h"
#include "GameAudio.h"
#include "Asteroid.h"
#include "Game.h"

namespace pure
{
	class Entity;
	class State;
	class StateManager;
}

class AsteroidsGame : public pure::Game
{
public:
	AsteroidsGame();
	~AsteroidsGame();

private:

	pure::StateManager m_stateManager;
	GameAudio m_audio;
	::Context m_ctx;

	virtual void onGameStart() final override;

	virtual void draw() final override;

	virtual void update(float deltaTime) final override;

	virtual void handleInput(const sf::Event& event) final override;


};

