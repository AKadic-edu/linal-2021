#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>

struct Camera {
	float top {};
	float bottom {};
	float left {};
	float right {};
	ml::Vector<float, 2> position;

	ml::Matrix<float, 3, 3> ortho() const;
};

#endif // !CAMERA_HPP
