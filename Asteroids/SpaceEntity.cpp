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

bool SpaceEntity::isActive() const
{
	return m_bActive;
}

void SpaceEntity::activate()
{
	m_bActive = true;
	onActivate();
}

void SpaceEntity::deactivate()
{
	m_bActive = false;
	onDeactivate();
}

void SpaceEntity::updateCurrent(float deltaTime)
{
	/// All entities in space should be constantly moving since there is no
	/// gravity or friction to slow them down...
	const Vector2f velocity = getVelocity();
	move(Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
}