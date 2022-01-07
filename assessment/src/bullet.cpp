#include "src/bullet.hpp"

#include <mathlib/utils/transforms.hpp>

#include "src/resources.hpp"

Bullet::Bullet(
	ml::Matrix<float, 4, 4> worldM,
	ml::Matrix<float, 4, 4> modelM,
	ml::Vector<float, 4> direction)
	: m_model{ vl::Model::create(cubeVertices) }
	, m_direction{ direction }
{
	//m_model.modelM = ml::scale(1.0f, 3.0f, 1.0f) * ml::scale(0.1f) * m_model.modelM;
	m_model.modelM = modelM * m_model.modelM;
	m_model.worldM = worldM;
}

void Bullet::update(float dt)
{
	auto translated = dt * 0.2f * (m_model.modelM * m_direction);
	auto translationM = ml::translate(ml::Vector<float, 3> { translated[0], translated[1], translated[2] });

	m_model.worldM = m_model.worldM * translationM;
}

void Bullet::draw(vl::Renderer& r, ml::Matrix<float, 4, 4> vp)
{
	r.color(0, 0, 0);
	r.drawModel(vp, m_model);
}
