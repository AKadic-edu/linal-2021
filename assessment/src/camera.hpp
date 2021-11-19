#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "assessment.hpp"

template<size_t N>
struct Camera {
	float top { 0.0f };
	float bottom { 0.0f };
	float left { 0.0f };
	float right { 0.0f };
	ml::Vector<float, N> position;
};

ml::Matrix<float, 3, 3> ortho(const Camera<2>& c, float aspect);
ml::Matrix<float, 4, 4> ortho(const Camera<3>& c, float aspect);
ml::Matrix<float, 3, 3> view(const Camera<2>& c);
ml::Matrix<float, 4, 4> view(const Camera<3>& c);

#endif // !CAMERA_HPP
