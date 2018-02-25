#pragma once

#include <SFML/Audio/Sound.hpp>
#include "SpaceEntity.h"
#include "WireFrameShape.h"
#include "Poolable.h"

template<typename T>
class ObjectPool;

class Asteroid : public SpaceEntity
{
public:

	enum class Size : int
	{
		Microscopic = 0, // Irrelevant, only used for overflows / nonexistant asteroids
		Small = 10,
		Medium = 20,
		Large = 30
	};

	virtual void update(float deltaTime) final override;

	// Gets size as an enum. (Underlying value is int as radius)
	Asteroid::Size getSize() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getMidOffset() const;

	void spawnAt(sf::Vector2f position, Asteroid::Size size);
	void setExplodeSound(const sf::SoundBuffer& buffer);
	void playExplodeSound();

	bool hasExplodeSound() const;

	bool detectCollision(class SpaceShip* spaceship);

protected:
	Asteroid();

private:
	static constexpr int m_vertCount = 30;

	enum class Speed : int
	{
		Still = 0,
		Slow = 150,
		Medium = 250,
		Fast = 300
	};

	friend Asteroid::Speed& operator--(Asteroid::Speed& s);
	friend Asteroid::Speed& operator++(Asteroid::Speed& s);

	WireFrameShape m_body;
	sf::Sound m_explodeSound;

	Speed m_activeSpeed;
	Asteroid::Size m_size;

	Asteroid(sf::Vector2f position, float radius);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void onDeactivate() final override;
};

Asteroid::Size& operator--(Asteroid::Size& s);
Asteroid::Size& operator++(Asteroid::Size& s);

typedef Poolable<Asteroid> PAsteroid;
