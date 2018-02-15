#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <assert.h>
#include "AsteroidPool.h"


AsteroidPool::AsteroidPool()
{
	m_asteroids.reserve(m_maxAsteroids);
	m_asteroids.assign(m_maxAsteroids, Asteroid());
	m_firstAvailable = &m_asteroids[0];

	for (size_t i = 0; i < m_asteroids.size() - 1; i++)
	{
		m_asteroids[i].setNext(&m_asteroids[i + 1]);
	}
	m_asteroids.back().setNext(nullptr);
}


AsteroidPool::~AsteroidPool()
{
}

Asteroid* AsteroidPool::create(sf::Vector2f position, float radius)
{
	assert(m_firstAvailable);

	Asteroid* asteroid = m_firstAvailable;
	asteroid->activate();
	asteroid->spawnAt(position, radius);

	m_firstAvailable = asteroid->getNext();

	return asteroid;
}

void AsteroidPool::destroy(Asteroid* asteroid)
{
	asteroid->deactivate();
	asteroid->setNext(m_firstAvailable);
	m_firstAvailable = asteroid;
}

