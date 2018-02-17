#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "SpaceEntity.h"
#include "Poolable.h"

template <typename T>
class ObjectPool;

class Bullet : public SpaceEntity
{
public:

	void spawnAt(sf::Vector2f position);
	bool isExpired() const;

	void update(float deltaTime) final override;

	// Gets the distance between center of entity and left (x) and top (y) 
	sf::Vector2f getMidOffset() const;

protected:
	Bullet();

private:
	static constexpr float m_radius = 1.f;
	// How long all bullets alive for in seconds
	static constexpr float m_duration = 5.f;

	sf::CircleShape m_body;
	Bullet* m_next;
	float m_timeActive;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	void onDeactivate() final override;
};

typedef Poolable<Bullet> PBullet;
