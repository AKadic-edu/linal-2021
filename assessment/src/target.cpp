#include "src/target.hpp"

#include <mathlib/utils/transforms.hpp>

#include "src/resources.hpp"

Target::Target()
	: m_model{ vl::Model::create(cubeVertices) }
	, m_animationSpeed { 1.0f }
	, m_currentSize { 1.0f }
{ }

void Target::update(float dt)
{
	if (m_currentSize <= MinSize || m_currentSize >= MaxSize) {
		m_animationSpeed = -m_animationSpeed;
	}

	m_currentSize += dt * m_animationSpeed;
	m_currentSize = ml::clamp(m_currentSize, MinSize, MaxSize);

	m_model.modelM[0][0] = m_currentSize;
	m_model.modelM[1][1] = m_currentSize;
	m_model.modelM[2][2] = m_currentSize;
}

void Target::draw(vl::Renderer& r, ml::Matrix<float, 4, 4> vp)
{
	r.color(0, 0, 0);
	r.drawModel(vp, m_model);
}

void Target::position(ml::Vector<float, 3> v)
{
	m_model.worldM = ml::translate(v) * m_model.worldM;
}
