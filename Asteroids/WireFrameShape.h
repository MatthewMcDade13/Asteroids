#pragma once

#include <SFML/Graphics/VertexArray.hpp>

namespace sf
{
	class Transform;

	template<typename T> class Rect;
	typedef Rect<float> FloatRect;

	template<typename T> class Vector2;
	typedef Vector2<float> Vector2f;
}

struct WireFrameShape
{
	sf::VertexArray shape;

	// Shorthand for m_body.getBounds();
	sf::FloatRect getLocalBounds() const;

	// Gets bounds of VertexArray body relative to the given transform.
	sf::FloatRect getGlobalBounds(const sf::Transform& transform) const;

	// Gets the distance between center of entity and left (x) and top (y) 
	sf::Vector2f getMidOffset() const;
};

