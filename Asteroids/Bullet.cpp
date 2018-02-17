#include "stdafx.h"
#include "GetRectCenter.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "DebugLog.h"

using namespace sf;

Bullet::Bullet():
	m_body(),
	m_next(nullptr),
	m_timeActive(0.f)
{
	m_body.setFillColor(Color::White);
	m_body.setRadius(m_radius);
	FloatRect bounds = m_body.getLocalBounds();
	m_body.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Bullet::spawnAt(sf::Vector2f position)
{
	setPosition(position);
	setOrigin(position);
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

sf::Vector2f Bullet::getMidOffset() const
{
	return getRectCenter(m_body.getLocalBounds());
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_body, getTransform());
}

void Bullet::onDeactivate()
{
	m_timeActive = 0.f;
	
}
