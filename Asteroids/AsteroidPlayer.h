#pragma once

#include <SFML/System/Clock.hpp>
#include "Player.h"
#include "SpaceShip.h"
#include "Bullet.h"

template <typename T>
class ObjectPool;

struct GameAudio;

class AsteroidPlayer : public pure::Player
{
public:
	AsteroidPlayer(ObjectPool<PBullet>* bulletPool, GameAudio* audio);
	~AsteroidPlayer();

	SpaceShip& getShip();
	//int getLivesLeft() const;

	void spawn(sf::Vector2f position);
	void die();
	void reset();

	bool isAlive() const;
	//bool canRespawn() const;

	//void grantLife();

	// Handles single polled sfml events
	virtual void handleEvent(const sf::Event& event) final override;

	virtual void setupKeybinds() final override;

private:
	static constexpr float m_fireCooldown = 0.3f;
	//static constexpr int m_startLives = 4;

	GameAudio* m_audio;
	sf::Clock m_fireTimer;
	SpaceShip m_spaceShip;
	ObjectPool<PBullet>* m_bulletPool;

	float m_rotationSpeed;
	float m_movementSpeed;
	float m_lastFireTime;
	//int m_lives;
};

