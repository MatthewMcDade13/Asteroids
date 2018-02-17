#pragma once

#include <chrono>
#include "Player.h"
#include "SpaceShip.h"
#include "Bullet.h"

template <typename T>
class ObjectPool;

class AsteroidPlayer : public pure::Player
{
public:
	AsteroidPlayer(ObjectPool<PBullet>* bulletPool);
	~AsteroidPlayer();

	void spawn(sf::Vector2f position);

	SpaceShip& getShip();

	// Handles single polled sfml events
	virtual void handleEvent(const sf::Event& event) final override;

	virtual void setupKeybinds() final override;

private:
	static constexpr float m_fireCooldown = 0.5f;

	SpaceShip m_spaceShip;
	ObjectPool<PBullet>* m_bulletPool;

	float m_rotationSpeed;
	float m_movementSpeed;

	float m_lastFireTime;
};

