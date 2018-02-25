#include "stdafx.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Constants.h"
#include "Random.h"
#include "Explosion.h"

using namespace sf;
using namespace pure;

Explosion::Explosion():
	m_duration(0.5f)
{
	m_particles.setPrimitiveType(Points);
	m_particles.resize(20);	
	m_particleVels.resize(20);
}


Explosion::~Explosion()
{
}

void Explosion::update(float deltaTime)
{
	if (m_timer.getElapsedTime().asSeconds() >= m_duration) return;
	for (size_t i = 0; i < m_particles.getVertexCount(); i++)
	{
		m_particles[i].position += m_particleVels[i] * deltaTime;
	}
}

void Explosion::spawnAt(const Vector2f & position)
{
	const Random rand;
	for (size_t i = 0; i < m_particles.getVertexCount(); i++)
	{
		m_particles[i].position = position;
		m_particles[i].color = Color::White;

		float angle = rand(360) * PI / 180.f;
		float speed = rand(100, 250);
		m_particleVels[i] = Vector2f(cosf(angle) * speed, sinf(angle) * speed);
	}

	m_timer.restart();
}

bool Explosion::isDone() const
{
	return m_timer.getElapsedTime().asSeconds() > m_duration;
}

void Explosion::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_particles);
}
