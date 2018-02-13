#pragma once

#include "StateManager.h"
#include "AsteroidPlayer.h"
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

	virtual void onGameStart() final override;

	virtual void draw() final override;

	virtual void update(float deltaTime) final override;

	virtual void handleInput(const sf::Event& event) final override;


};

