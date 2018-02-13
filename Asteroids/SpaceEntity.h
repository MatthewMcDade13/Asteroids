#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include "Printable.h"
#include "Entity.h"

namespace sf
{
	template<typename T> class Rect;
	template<typename T> class Vector2;

	typedef Rect<float> FloatRect;
	typedef Vector2<float> Vector2f;
}

class SpaceEntity : public pure::Entity
{
public:

	SpaceEntity();
	virtual ~SpaceEntity();

	bool isActive() const;

	void activate();
	void deactivate();

	// Gets the distance between center of entity and left (x) and top (y) 
	sf::Vector2f getMidOffset() const;

	//bool collision(SpaceEntity* other);

protected:

	// Updates the current Scene Node
	virtual void updateCurrent(float deltaTime) override;
	virtual void onActivate() { }
	virtual void onDeactivate() { }

private:
	bool m_bActive;
};

