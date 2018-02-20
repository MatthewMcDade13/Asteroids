#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "State.h"

namespace pure
{
	class StateManager;
	struct ResourceHolder;
}

class GameOverState : public pure::State
{
public:
	GameOverState(pure::StateManager* manager, pure::ResourceHolder* resources);
	~GameOverState();

	virtual void update(float deltaTime) final override;

	virtual void draw(sf::RenderWindow& window) final override;

private:
	pure::ResourceHolder* m_resources;
	sf::Text m_gameOverText;
	sf::Text m_resumeText;
	sf::RectangleShape m_background;

	// Called when state is created from state manager.
	virtual void onCreate() final override;
	virtual void handleInput(const sf::Event& event) final override;
};

