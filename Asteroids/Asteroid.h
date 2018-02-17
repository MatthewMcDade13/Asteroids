#pragma once

#include "SpaceEntity.h"
#include "WireFrameShape.h"
#include "Poolable.h"

template<typename T>
class ObjectPool;

class Asteroid : public SpaceEntity
{
public:
	//friend class AsteroidPool;
	//friend ObjectPool<PAsteroid>;
	// Stores given speed and sets velocity equal to speed
	void setSpeed(float speed);
	virtual void update(float deltaTime) final override;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

	void spawnAt(sf::Vector2f position, float radius);

protected:
	Asteroid();

private:
	static constexpr int m_vertCount = 30;

	WireFrameShape m_body;
	float m_speed;

	Asteroid(sf::Vector2f position, float radius);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void onDeactivate() final override;
};

typedef Poolable<Asteroid> PAsteroid;
