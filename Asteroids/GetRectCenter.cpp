#include "stdafx.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "GetRectCenter.h"

using namespace sf;

Vector2f getRectCenter(const FloatRect& rect)
{
	const FloatRect bodySize = rect;
	const float x = bodySize.width / 2;
	const float y = bodySize.height / 2;
	return Vector2f(x, y);
}
