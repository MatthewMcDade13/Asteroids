#include "stdafx.h"
#include "GetRectCenter.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::spawnAt(sf::Vector2f position)
{

}

sf::Vector2f Bullet::getMidOffset() const
{
	return getRectCenter(m_body.getLocalBounds());
}
