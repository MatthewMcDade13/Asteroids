#include "stdafx.h"
#include "Constants.h"
#include "SpaceShip.h"
#include "AsteroidPlayer.h"
#include "Conversions.h"

using namespace std; 
using namespace pure;
using namespace sf;

AsteroidPlayer::AsteroidPlayer():
	m_spaceShip(),
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

void AsteroidPlayer::handleEvent(const Event & event)
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
}
