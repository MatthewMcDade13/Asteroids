#pragma once

namespace sf
{
	template<typename T> class Vector2;
	typedef Vector2<float> Vector2f;

	template<typename T> class Rect;
	typedef Rect<float> FloatRect;
}

sf::Vector2f getRectCenter(const sf::FloatRect& rect);
