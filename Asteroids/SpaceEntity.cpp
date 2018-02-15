#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "SpaceEntity.h"
#include "VecToString.h"

using namespace sf; using namespace std; using namespace pure;

SpaceEntity::SpaceEntity()
{
}

SpaceEntity::~SpaceEntity()
{
}


void SpaceEntity::update(float deltaTime)
{
	/// All entities in space should be constantly moving since there is no
	/// gravity or friction to slow them down...
	const Vector2f velocity = getVelocity();
	move(Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
}