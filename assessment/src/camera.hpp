#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "assessment.hpp"

template<size_t N>
struct Camera {
	float top;
	float bottom;
	float left;
	float right;
	ml::Vector<float, N> up;
	ml::Vector<float, N> position;
	ml::Vector<float, N> target;
};

ml::Matrix<float, 3, 3> ortho(const Camera<2>& c, float aspect);
ml::Matrix<float, 4, 4> ortho(const Camera<3>& c, float aspect);
ml::Matrix<float, 3, 3> view(const Camera<2>& c);
ml::Matrix<float, 4, 4> view(const Camera<3>& c);

#endif // !CAMERA_HPP
