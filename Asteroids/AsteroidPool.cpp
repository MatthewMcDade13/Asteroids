#include "stdafx.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <assert.h>
#include "AsteroidPool.h"

using namespace std;

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

	m_activeAsteroids.reserve(m_maxAsteroids);
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

	const int indx = m_activeAsteroids.size();
	m_activeAsteroids.push_back(make_pair(asteroid, indx));

	return asteroid;
}

void AsteroidPool::destroy(Asteroid* asteroid)
{
	asteroid->deactivate();
	asteroid->setNext(m_firstAvailable);
	m_firstAvailable = asteroid;

	auto itr = find_if(m_activeAsteroids.begin(), m_activeAsteroids.end(),
		[asteroid](auto& a) {
		return a.first == asteroid;
	});

	m_activeAsteroids.erase(itr);
}

void AsteroidPool::destroy(int asteroidIndx)
{
	Asteroid* asteroid = m_activeAsteroids[asteroidIndx].first;

	asteroid->deactivate();
	asteroid->setNext(m_firstAvailable);
	m_firstAvailable = asteroid;

	m_activeAsteroids.erase(m_activeAsteroids.begin() + asteroidIndx);
}

const std::vector<std::pair<Asteroid*, int>>& AsteroidPool::getActiveAsteroids() const
{
	return m_activeAsteroids;
}

