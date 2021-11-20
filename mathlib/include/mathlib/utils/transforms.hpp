#pragma once

#ifndef MATHLIB_TRANSFORMS_H
#define MATHLIB_TRANSFORMS_H

#include <cmath>

#include "operations.hpp"
#include "../matrix.hpp"
#include "../vector.hpp"

namespace ml {
	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, N, M> rotate(const Matrix<T, N, M>& m, float a)
	{
		Matrix<T, M, N> rotationM;

		rotationM[0][0] = (a == 90.0f || a == -90.0f) ? 0.0f : (float)(std::cos(radians(a)));
		rotationM[0][1] =  (float)(std::sin(radians(a)));
		rotationM[1][0] = -(float)(std::sin(radians(a)));
		rotationM[1][1] = (a == 90.0f || a == -90.0f) ? 0.0f : (float)(std::cos(radians(a)));

		return rotationM * m;
	}

	template<typename T>
	constexpr Matrix<T, 4, 4> rotate(const Matrix<T, 4, 4>& m, Vector<T, 3> r)
	{
		auto xM = identity<T, 4, 4>();
		xM[1][1] = (r[0] == 90.0f || r[0] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[0])));
		xM[1][2] = (float)(std::sin(radians(r[0])));
		xM[2][1] = -(float)(std::sin(radians(r[0])));
		xM[2][2] = (r[0] == 90.0f || r[0] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[0])));

		auto yM = identity<T, 4, 4>();
		yM[0][0] = (r[1] == 90.0f || r[1] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[1])));
		yM[0][2] = -(float)(std::sin(radians(r[1])));
		yM[2][0] = (float)(std::sin(radians(r[1])));
		yM[2][2] = (r[1] == 90.0f || r[1] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[1])));

		auto zM = identity<T, 4, 4>();
		zM[0][0] = (r[2] == 90.0f || r[2] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[2])));
		zM[0][1] = (float)(std::sin(radians(r[2])));
		zM[1][0] = -(float)(std::sin(radians(r[2])));
		zM[1][1] = (r[2] == 90.0f || r[2] == -90.0f) ? 0.0f : (float)(std::cos(radians(r[2])));

		return zM * yM * xM * m;
	}
}

#endif // !MATHLIB_TRANSFORMS_H
