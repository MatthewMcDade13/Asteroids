#include "stdafx.h"
#include <random>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>
#include "CreateVertSquare.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Constants.h"
#include "VectorMath.h"
#include "Random.h"
#include "DebugLog.h"

using namespace sf; 
using namespace std;
using namespace pure;

Asteroid::Asteroid()
{
	m_body.shape.setPrimitiveType(LineStrip);
}

Asteroid::Asteroid(Vector2f position, float radius)
{
	m_body.shape.setPrimitiveType(LineStrip);
	spawnAt(position, Size::Large);
}

void Asteroid::spawnAt(Vector2f position, Asteroid::Size size)
{
	setOrigin(position);
	setPosition(position);
	m_size = size;
	const float radius = static_cast<float>(m_size);

	const Vector2f& center = position;

	/// divide circle up by number of verts
	const float step = (2 * pure::PI) / m_vertCount;
	const Random rand;

	for (float theta = 0; theta < (2 * pure::PI); theta += step)
	{
		float x = (center.x + radius * cosf(theta)) + rand(-3, 3);
		float y = (center.y - radius * sinf(theta)) + rand(-3, 3);
		Vertex vert(Vector2f(x, y));
		vert.color = Color::Yellow;
		m_body.shape.append(vert);
	}

	// Copy the first vert to connect the last vert and close the 'circle'
	m_body.shape.append(Vertex(m_body.shape[0]));
	m_body.updateBounds();

	switch (size)
	{
		case Size::Small:
			m_activeSpeed = Speed::Fast;
			break;
		case Size::Medium:
			m_activeSpeed = Speed::Medium;
			break;
		case Size::Large:
			m_activeSpeed = Speed::Slow;
			break;
	}
	const int speed = static_cast<int>(m_activeSpeed);
	setVelocity(speed * rand(-1.f, 1.f), speed * rand(-1.f, 1.f));
}

bool Asteroid::detectCollision(SpaceShip* spaceship)
{
	return spaceship->getGlobalBounds().intersects(getGlobalBounds());
}

Asteroid::Size Asteroid::getSize() const
{
	return m_size;
}

sf::FloatRect Asteroid::getLocalBounds() const
{
	return m_body.getLocalBounds();
}

FloatRect Asteroid::getGlobalBounds() const
{
	return m_body.getGlobalBounds(getPosition(), getOrigin());
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

void Asteroid::onDeactivate()
{
	m_body.shape.clear();
}

Asteroid::Speed& operator--(Asteroid::Speed& s)
{
	switch (s)
	{
		case Asteroid::Speed::Fast:
			s = Asteroid::Speed::Medium;
			return s;
		case Asteroid::Speed::Medium:
			s = Asteroid::Speed::Slow;
			return s;
		case Asteroid::Speed::Slow:
			s = Asteroid::Speed::Still;
			return s;
		default:
			s = Asteroid::Speed::Still;
			return s;
	}
}

Asteroid::Speed& operator++(Asteroid::Speed& s)
{
	switch (s)
	{
		case Asteroid::Speed::Still:
			s = Asteroid::Speed::Slow;
			return s;
		case Asteroid::Speed::Slow:
			s = Asteroid::Speed::Medium;
			return s;
		case Asteroid::Speed::Medium:
			s = Asteroid::Speed::Fast;
			return s;
		case Asteroid::Speed::Fast:
			s = Asteroid::Speed::Fast;
			return s;
		default:
			s = Asteroid::Speed::Still;
			return s;
	}
}

Asteroid::Size& operator--(Asteroid::Size& s)
{
	switch (s)
	{
		case Asteroid::Size::Large:
			s = Asteroid::Size::Medium;
			return s;
		case Asteroid::Size::Medium:
			s = Asteroid::Size::Small;
			return s;
		default:
			s = Asteroid::Size::Microscopic;
			return s;
	}
}

Asteroid::Size& operator++(Asteroid::Size& s)
{
	switch (s)
	{
		case Asteroid::Size::Large:
			s = Asteroid::Size::Large;
			return s;
		case Asteroid::Size::Medium:
			s = Asteroid::Size::Large;
			return s;
		case Asteroid::Size::Small:
			s = Asteroid::Size::Medium;
			return s;
		case Asteroid::Size::Microscopic:
			s = Asteroid::Size::Small;
			return s;
		default:
			s = Asteroid::Size::Microscopic;
			return s;
	}
}
