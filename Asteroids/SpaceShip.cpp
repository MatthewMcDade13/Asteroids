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
}

void SpaceShip::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_body.shape, getTransform());
}

