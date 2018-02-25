#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Audio/Sound.hpp>
#include "WireFrameShape.h"
#include "SpaceEntity.h"

namespace sf
{
	class VertexArray;
	typedef Vector2<float> Vector2f;
}

class Bullet;

class SpaceShip final : public SpaceEntity
{
public:
	// creates spaceship with default values
	SpaceShip();

	// creates and spawns spaceship at target location
	SpaceShip(sf::Vector2f position);
	~SpaceShip();

	void spawnAt(sf::Vector2f position);
	void setFireSound(const sf::SoundBuffer& buffer);
	void setExplodeSound(const sf::SoundBuffer& buffer);
	void playExplodeSound();


	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

	void fire(Bullet* bullet) const;

private:
	static constexpr float m_bulletSpeed = 500.f;
	WireFrameShape m_body;
	mutable sf::Sound m_fireSound;
	sf::Sound m_explodeSound;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void onDeactivate() final override;
};


