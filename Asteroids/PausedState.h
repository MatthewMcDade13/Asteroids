#pragma once
#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Context;

namespace pure
{
	class StateManager;
	struct ResourceHolder;
}

class PausedState : public pure::State
{
public:
	PausedState(pure::StateManager* manager, ::Context* ctx);
	~PausedState();

	virtual void update(float deltaTime) final override;

	virtual void draw(sf::RenderWindow& window)  final override;

private:
	Context* m_ctx;
	sf::Text m_pauseText;
	sf::Text m_settingsText;
	sf::RectangleShape m_background;

	void updateSettingsText();

	// Called when state is created from state manager.
	virtual void onCreate() final override;

	virtual void handleInput(const sf::Event& event) final override;
	virtual void onActivate() final override;
};

