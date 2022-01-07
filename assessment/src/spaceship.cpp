#include "src/spaceship.hpp"

#include <mathlib/utils/transforms.hpp>

#include "src/resources.hpp"

Spaceship::Spaceship()
	: m_model{ vl::Model::create(spaceshipVertices) }
	, m_direction { 0.0f, 1.0f, 0.0f, 1.0f }
{
	m_model.modelM = ml::rotate(0.0f, 0.0f, -90.0f) * ml::scale(1.0f, 2.0f, 1.0f) * ml::scale(0.5f) * m_model.modelM;
}

void Spaceship::update(float dt)
{
	auto translated = dt * Speed * (m_model.modelM * m_direction);
	m_model.worldM = m_model.worldM * ml::translate(ml::Vector<float, 3> { translated[0], translated[1], translated[2] });
}

void Spaceship::draw(vl::Renderer& r, ml::Matrix<float, 4, 4> vp)
{
	r.color(0, 0, 0);
	r.drawModel(vp, m_model);
}

void Spaceship::fire()
{
	//auto translated = m_model.modelM * m_direction;
}

void Spaceship::steer(ml::Vector<float, 3> v)
{
	m_model.modelM = ml::rotate(v) *  m_model.modelM;
}
