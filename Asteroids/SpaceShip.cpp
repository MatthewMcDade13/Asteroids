#include "stdafx.h"
#include "Bullet.h"
#include "SpaceShip.h"
#include "DebugLog.h"

using namespace sf; using namespace std;

SpaceShip::SpaceShip()
{
	m_body.shape.setPrimitiveType(LineStrip);
	m_body.shape.resize(4);
}

SpaceShip::SpaceShip(Vector2f position)
{
	m_body.shape.setPrimitiveType(LineStrip);
	m_body.shape.resize(4);
	spawnAt(position);
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::spawnAt(Vector2f position)
{
	setOrigin(position);
	setPosition(position);

	m_body.shape[0] = Vertex(Vector2f(position.x, position.y - 25.f));
	m_body.shape[1] = Vertex(Vector2f(position.x - 12.5f, position.y + 12.5f));
	m_body.shape[2] = Vertex(Vector2f(position.x + 12.5f, position.y + 12.5f));
	m_body.shape[3] = Vertex(Vector2f(position.x, position.y - 25.f));
	m_body.updateBounds();
}

void SpaceShip::setFireSound(const sf::SoundBuffer & buffer)
{
	m_fireSound.setBuffer(buffer);
}

void SpaceShip::setExplodeSound(const sf::SoundBuffer & buffer)
{
	m_explodeSound.setBuffer(buffer);
}

void SpaceShip::playExplodeSound()
{
	m_explodeSound.play();
}

FloatRect SpaceShip::getLocalBounds() const
{
	return m_body.getLocalBounds();
}

FloatRect SpaceShip::getGlobalBounds() const
{
	return m_body.getGlobalBounds(getTransform());
}

Vector2f SpaceShip::getMidOffset() const
{
	return m_body.getMidOffset();
}

void SpaceShip::fire(Bullet* bullet) const
{
	bullet->spawnAt(getPosition());
	bullet->setVelocity(getForwardDirection() * m_bulletSpeed);

	if (m_fireSound.getBuffer()) m_fireSound.play();
}

void SpaceShip::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_body.shape, getTransform());
}

void SpaceShip::onDeactivate()
{
	m_body.shape.clear();
	m_body.shape.resize(4);
	setVelocity(0.f, 0.f);
	setRotation(0.f);
}

