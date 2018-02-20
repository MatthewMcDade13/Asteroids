#include "stdafx.h"
#include "GetRectCenter.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "Asteroid.h"
#include "DebugLog.h"

using namespace sf;

Bullet::Bullet():
	m_body(),
	m_timeActive(0.f)
{
	m_body.setFillColor(Color::White);
	m_body.setRadius(m_radius);
	const FloatRect bounds = m_body.getLocalBounds();
	m_body.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Bullet::spawnAt(sf::Vector2f position)
{
	setOrigin(position);
	setPosition(position);

	m_body.setPosition(position);

}

bool Bullet::isExpired() const
{
	return m_timeActive >= m_duration;
}

void Bullet::update(float deltaTime)
{
	SpaceEntity::update(deltaTime);
	m_timeActive += deltaTime;
}

Vector2f Bullet::getMidOffset() const
{
	return getRectCenter(m_body.getLocalBounds());
}

FloatRect Bullet::getGlobalBounds() const
{
	return getTransform().transformRect(m_body.getGlobalBounds());
}

bool Bullet::detectCollision(Asteroid* ast) const
{
	return ast->getGlobalBounds().intersects(getGlobalBounds());
}

void Bullet::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_body, getTransform());
}

void Bullet::onDeactivate()
{
	m_timeActive = 0.f;
}
