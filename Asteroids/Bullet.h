#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "SpaceEntity.h"

class Bullet : public SpaceEntity
{
public:
	// How long all bullets alive for in milliseconds
	static constexpr float duration = 5.f;

	Bullet();
	~Bullet();

	void spawnAt(sf::Vector2f position);

	// Gets the distance between center of entity and left (x) and top (y) 
	sf::Vector2f getMidOffset() const;

private:
	static constexpr float m_radius = 1.f;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	sf::CircleShape m_body;
};

