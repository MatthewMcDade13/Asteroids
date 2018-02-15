#include "stdafx.h"
#include <SFML/Graphics/Transform.hpp>
#include "GetRectCenter.h"
#include "WireFrameShape.h"

using namespace sf;

FloatRect WireFrameShape::getLocalBounds() const
{
	return shape.getBounds();
}

FloatRect WireFrameShape::getGlobalBounds(const Transform& transform) const
{
	VertexArray temp = shape;

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		temp[i].position = transform.transformPoint(temp[i].position);
	}

	return temp.getBounds();;
}

Vector2f WireFrameShape::getMidOffset() const
{
	return getRectCenter(getLocalBounds());
}
