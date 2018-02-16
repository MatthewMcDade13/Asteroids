#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <utility>
#include "Asteroid.h"

namespace sf
{
	class RenderWindow;
}

class AsteroidPool
{
public:
	AsteroidPool();
	~AsteroidPool();

	Asteroid* create(sf::Vector2f position, float radius);
	void destroy(Asteroid* asteroid);
	void destroy(int asteroidIndx);

	const std::vector<std::pair<Asteroid*, int>>& getActiveAsteroids() const;

private:
	static constexpr int m_maxAsteroids = 255;

	std::vector<Asteroid> m_asteroids;
	std::vector<std::pair<Asteroid*, int>> m_activeAsteroids;
	Asteroid* m_firstAvailable;
};

