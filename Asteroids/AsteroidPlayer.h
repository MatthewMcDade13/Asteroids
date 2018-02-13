#pragma once

#include "Player.h"
#include "SpaceShip.h"

class AsteroidPlayer : public pure::Player
{
public:
	AsteroidPlayer();
	~AsteroidPlayer();

	void spawn(sf::Vector2f position);

	SpaceShip& getShip();

	// Handles single polled sfml events
	virtual void handleEvent(const sf::Event& event) final override;

	virtual void setupKeybinds() final override;

private:
	SpaceShip m_spaceShip;
	float m_rotationSpeed;
	float m_movementSpeed;
};

