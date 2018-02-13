#pragma once

#include "State.h"
#include "Entity.h"
#include "AsteroidPlayer.h"
#include "Asteroid.h"
#include <vector>
#include <memory>
#include <SFML/System/NonCopyable.hpp>

namespace pure
{
	class StateManager;
	struct ResourceHolder;
}

class PlayState final : public pure::State, private sf::NonCopyable
{
public:
	PlayState(pure::StateManager* manager, pure::ResourceHolder* resources);
	~PlayState();

	virtual void update(float deltaTime) final override;

	virtual void draw(sf::RenderWindow& window) final override;

	// Called when state is created from state manager.
	virtual void onCreate() final override;

private:

	AsteroidPlayer m_player;
	std::vector<std::unique_ptr<Asteroid>> m_asteroids;
	pure::ResourceHolder* m_resources;

	template <typename EmbodiedEntity>
	void clampEntity(EmbodiedEntity& entity)
	{
		const Vector2f offset = entity.getMidOffset();

		if (entity.getPosition().x + offset.x < 0)
		{
			entity.setPosition(getWindow().getSize().x + offset.x, entity.getPosition().y);
		}
		else if (entity.getPosition().x - offset.x > getWindow().getSize().x)
		{
			entity.setPosition(-(offset.x), entity.getPosition().y);
		}
		else if (entity.getPosition().y + offset.y < 0)
		{
			entity.setPosition(entity.getPosition().x, getWindow().getSize().y + offset.y);
		}
		else if (entity.getPosition().y - offset.y > getWindow().getSize().y)
		{
			entity.setPosition(entity.getPosition().x, -(offset.y));
		}
	}

	const sf::RenderWindow& getWindow() const;

	virtual void handleInput(const sf::Event& event) final override;
	
};

