#pragma once

#ifndef BULLET_HPP
#define BULLET_HPP

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <videolib/model.hpp>
#include <videolib/renderer.hpp>

class Bullet {
public:
	Bullet(
		ml::Matrix<float, 4, 4> worldM,
		ml::Matrix<float, 4, 4> modelM,
		ml::Vector<float, 4> direction);

	void update(float);
	void draw(vl::Renderer&, ml::Matrix<float, 4, 4> vp);
private:
	ml::Vector<float, 4> m_direction;
	vl::Model m_model;
};

#endif // !BULLET_HPP
