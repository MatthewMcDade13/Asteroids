#pragma once

#include "SpaceEntity.h"
#include "WireFrameShape.h"

class Asteroid final : public SpaceEntity
{
public:
	Asteroid();
	Asteroid(sf::Vector2f position, float radius);
	~Asteroid();

	void spawnAt(sf::Vector2f position, float radius);

	// Stores given speed and sets velocity equal to speed
	void setSpeed(float speed);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

private:
	static constexpr int m_vertCount = 30;

	WireFrameShape m_body;
	float m_speed;

	// Draws the current Scene Node.
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const final override;

	// Updates the current Scene Node
	virtual void updateCurrent(float deltaTime) final override;

	virtual void onDeactivate() final override;
};

