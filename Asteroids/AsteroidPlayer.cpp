#include "stdafx.h"
#include "Constants.h"
#include "SpaceShip.h"
#include "AsteroidPlayer.h"
#include "Conversions.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "DebugLog.h"

using namespace std; 
using namespace pure;
using namespace sf;

AsteroidPlayer::AsteroidPlayer(ObjectPool<PBullet>* bulletPool):
	m_spaceShip(),
	m_bulletPool(bulletPool),
	m_rotationSpeed(200.f),
	m_movementSpeed(250.f)
{
}

AsteroidPlayer::~AsteroidPlayer()
{
}

void AsteroidPlayer::spawn(Vector2f position)
{
	m_spaceShip.spawnAt(position);
}

SpaceShip& AsteroidPlayer::getShip()
{
	return m_spaceShip;
}

void AsteroidPlayer::handleEvent(const Event& event)
{
}

void AsteroidPlayer::setupKeybinds()
{
	bindKey(Keyboard::W, [this](float dt) {
		const float playerRot = radians(m_spaceShip.getRotation());

		const Vector2f vel = m_spaceShip.getForwardDirection() * m_movementSpeed * dt;
		m_spaceShip.addVelocity(vel);
	});

	bindKey(Keyboard::A, [this](float dt) {
		m_spaceShip.rotate(-m_rotationSpeed * dt);
	});

	bindKey(Keyboard::D, [this](float dt) {
		m_spaceShip.rotate(m_rotationSpeed * dt);
	});

	bindKey(Keyboard::Space, [this](float dt) {
		auto time = chrono::system_clock::now().time_since_epoch();

		bool canFire = (time.count() - m_lastFireTime) >= m_fireCooldown;

		dbLog("ELAPSED TIME: ", (time.count() - (long long)m_lastFireTime));

		if (canFire)
		{
			Bullet* bullet = m_bulletPool->create();
			m_spaceShip.fire(bullet);
			time = chrono::system_clock::now().time_since_epoch();
			m_lastFireTime = time.count();
		}
	});
}
