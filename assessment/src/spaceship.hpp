#pragma once

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <mathlib/vector.hpp>
#include <videolib/model.hpp>
#include <videolib/renderer.hpp>

class Spaceship {
public:
	Spaceship();

	void update(float dt);
	void draw(vl::Renderer&, ml::Matrix<float, 4, 4> vp);
private:
	const float Speed = 0.2f;

	ml::Vector<float, 3> m_direction;
	vl::Model m_model;
};

#endif // !SPACESHIP_HPP
