#include "stdafx.h"
#include "GetRectCenter.h"
#include "Bullet.h"

using namespace sf;

Bullet::Bullet()
{
	m_body.setFillColor(Color::White);
	m_body.setRadius(m_radius);
}


Bullet::~Bullet()
{
}

void Bullet::spawnAt(sf::Vector2f position)
{
	m_body.setOrigin(position);
	m_body.setPosition(position);
}

sf::Vector2f Bullet::getMidOffset() const
{
	return getRectCenter(m_body.getLocalBounds());
}

void Bullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
