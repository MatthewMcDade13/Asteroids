#include "stdafx.h"
#include <random>
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Constants.h"
#include "VectorMath.h"
#include "DebugLog.h"

using namespace sf; 
using namespace std;

Asteroid::Asteroid()
{
	m_body.shape.setPrimitiveType(LineStrip);
	//m_body.shape.resize(m_vertCount + 1); // Add one to make room for the last vertex that will close the 'circle'
}

Asteroid::Asteroid(Vector2f position, float radius)
{
	m_body.shape.setPrimitiveType(LineStrip);
	//m_body.shape.resize(m_vertCount + 1);
	spawnAt(position, radius);
}

void Asteroid::spawnAt(Vector2f position, float radius)
{
	setOrigin(position);
	setPosition(position);
	const Vector2f& center = position;

	/// divide circle up by number of verts
	const float step = (2 * pure::PI) / m_vertCount;
	random_device rd;
	mt19937 rand(rd());
	uniform_int_distribution<int> randOffset(-3, 3);	// random offset to produce 'jagged' shape

	for (float theta = 0; theta < (2 * pure::PI); theta += step)
	{
		float x = (center.x + radius * cosf(theta)) + randOffset(rand);
		float y = (center.y - radius * sinf(theta)) + randOffset(rand);
		Vertex vert(Vector2f(x, y));
		vert.color = Color::Yellow;
		m_body.shape.append(vert);
	}

	// Copy the first vert to connect the last vert and close the 'circle'
	m_body.shape.append(Vertex(m_body.shape[0]));

}

void Asteroid::setSpeed(float speed)
{
	m_speed = speed;
	setVelocity(m_speed, m_speed);
}

sf::FloatRect Asteroid::getLocalBounds() const
{
	return m_body.getLocalBounds();
}

sf::FloatRect Asteroid::getGlobalBounds() const
{
	return m_body.getGlobalBounds(getTransform());
}

sf::Vector2f Asteroid::getMidOffset() const
{
	return m_body.getMidOffset();
}

void Asteroid::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_body.shape, getTransform());
}

void Asteroid::update(float deltaTime)
{
	SpaceEntity::update(deltaTime);
	rotate(50.f * deltaTime);
}

Asteroid * Asteroid::getNext() const
{
	return m_next;
}

void Asteroid::setNext(Asteroid* next)
{
	m_next = next;
}

void Asteroid::onDeactivate()
{
	m_body.shape.clear();
}

