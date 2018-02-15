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
	
	virtual void update(float deltaTime) override;
};

