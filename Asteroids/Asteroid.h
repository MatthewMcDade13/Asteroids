#pragma once

#include "SpaceEntity.h"
#include "WireFrameShape.h"

class Asteroid final : public SpaceEntity
{
public:
	friend class AsteroidPool;
	// Stores given speed and sets velocity equal to speed
	void setSpeed(float speed);
	virtual void update(float deltaTime) final override;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

private:
	static constexpr int m_vertCount = 30;

	WireFrameShape m_body;
	Asteroid* m_next;
	float m_speed;

	Asteroid();
	Asteroid(sf::Vector2f position, float radius);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void onDeactivate() final override;

	Asteroid* getNext() const;
	void setNext(Asteroid* next);

	void spawnAt(sf::Vector2f position, float radius);

};

