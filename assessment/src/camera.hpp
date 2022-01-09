#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "assessment.hpp"

template<size_t N>
struct Camera {
	ml::Vector<float, N> up;
	ml::Vector<float, N> position;
	ml::Vector<float, N> target;
};

ml::Matrix<float, 3, 3> ortho(const Camera<2>& c, float t, float b, float l, float r, float aspect);
ml::Matrix<float, 4, 4> ortho(const Camera<3>& c, float t, float b, float l, float r, float aspect);
ml::Matrix<float, 4, 4> perspective(const Camera<3>& c, float far, float near, float fov);
ml::Matrix<float, 3, 3> view(const Camera<2>& c);
ml::Matrix<float, 4, 4> view(const Camera<3>& c);

#endif // !CAMERA_HPP
