#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include "WireFrameShape.h"
#include "SpaceEntity.h"

namespace sf
{
	class VertexArray;
	typedef Vector2<float> Vector2f;
}

class SpaceShip final : public SpaceEntity
{
public:
	// creates spaceship with default values
	SpaceShip();

	// creates and spawns spaceship at target location
	SpaceShip(sf::Vector2f position);
	~SpaceShip();

	void spawnAt(sf::Vector2f position);


	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

private:
	WireFrameShape m_body;
	// Draws the current Scene Node.
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const final override;
};


