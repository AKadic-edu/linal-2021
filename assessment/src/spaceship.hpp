#pragma once

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <mathlib/vector.hpp>
#include <videolib/model.hpp>
#include <videolib/renderer.hpp>

#include "src/bullet.hpp"

class Spaceship {
public:
	Spaceship();

	void update(float dt);
	void draw(vl::Renderer&, ml::Matrix<float, 4, 4> vp);

	void fire();
	void steer(ml::Vector<float, 3>);
	void toggleGas();
private:
	const float Speed = 0.2f;

	float m_acceleration;
	ml::Vector<float, 4> m_direction;
	vl::Model m_model;
	std::vector<Bullet> m_bullets;
};

#endif // !SPACESHIP_HPP
