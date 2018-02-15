#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <functional>
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

private:
	static constexpr int m_maxAsteroids = 255;

	std::vector<Asteroid> m_asteroids;
	Asteroid* m_firstAvailable;
};

