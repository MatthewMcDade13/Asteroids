#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include "Poolable.h"

class Explosion final : public sf::Drawable
{
public:
	Explosion();
	~Explosion();

	void update(float deltaTime);
	void spawnAt(const sf::Vector2f& position);

	bool isDone() const;

private:
	sf::Clock m_timer;
	sf::VertexArray m_particles;
	std::vector<sf::Vector2f> m_particleVels;

	float m_duration;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
};

typedef Poolable<Explosion> PExplosion;