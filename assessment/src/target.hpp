#pragma once

#ifndef TARGET_HPP
#define TARGET_HPP

#include <mathlib/vector.hpp>
#include <videolib/model.hpp>
#include <videolib/renderer.hpp>

#include "src/bullet.hpp"

class Target {
public:
	Target();

	void update(float);
	void draw(vl::Renderer&, ml::Matrix<float, 4, 4> vp);

	void position(ml::Vector<float, 3>);
private:
	const float MinSize = 1.0f;
	const float MaxSize = 2.0f;
	float m_animationSpeed;
	float m_currentSize;

	vl::Model m_model;
};

#endif // !TARGET_HPP
