#pragma once
#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace pure
{
	class StateManager;
	struct ResourceHolder;
}

class PausedState : public pure::State
{
public:
	PausedState(pure::StateManager* manager, pure::ResourceHolder* resources);
	~PausedState();

	virtual void update(float deltaTime) final override;

	virtual void draw(sf::RenderWindow& window)  final override;

private:
	pure::ResourceHolder* m_resources;
	sf::Text m_pauseText;
	sf::RectangleShape m_background;

	// Called when state is created from state manager.
	virtual void onCreate() final override;

	virtual void handleInput(const sf::Event& event) final override;
};

