#include "stdafx.h"
#include "SpaceShip.h"

using namespace sf;

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

sf::FloatRect SpaceShip::getLocalBounds() const
{
	return m_body.getLocalBounds();
}

sf::FloatRect SpaceShip::getGlobalBounds() const
{
	return m_body.getGlobalBounds(getTransform());
}

sf::Vector2f SpaceShip::getMidOffset() const
{
	return m_body.getMidOffset();
}

void SpaceShip::drawCurrent(RenderTarget& target, RenderStates states) const
{
	target.draw(m_body.shape, getTransform());
}

