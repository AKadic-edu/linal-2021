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
	constexpr Matrix<T, 4, 4> rotate(T x, T y, T z)
	{
		auto xM = identity<T, 4, 4>();
		xM[1][1] = (x == 90.0f || x == -90.0f) ? 0.0f : (float)(std::cos(radians(x)));
		xM[1][2] = (float)(std::sin(radians(x)));
		xM[2][1] = -(float)(std::sin(radians(x)));
		xM[2][2] = (x == 90.0f || x == -90.0f) ? 0.0f : (float)(std::cos(radians(x)));

		auto yM = identity<T, 4, 4>();
		yM[0][0] = (y == 90.0f || y == -90.0f) ? 0.0f : (float)(std::cos(radians(y)));
		yM[0][2] = -(float)(std::sin(radians(y)));
		yM[2][0] = (float)(std::sin(radians(y)));
		yM[2][2] = (y == 90.0f || y == -90.0f) ? 0.0f : (float)(std::cos(radians(y)));

		auto zM = identity<T, 4, 4>();
		zM[0][0] = (z == 90.0f || z == -90.0f) ? 0.0f : (float)(std::cos(radians(z)));
		zM[0][1] = (float)(std::sin(radians(z)));
		zM[1][0] = -(float)(std::sin(radians(z)));
		zM[1][1] = (z == 90.0f || z == -90.0f) ? 0.0f : (float)(std::cos(radians(z)));

		return zM * yM * xM;
	}

	template<typename T>
	constexpr Matrix<T, 4, 4> scale(T x, T y, T z)
	{
		auto m = identity<T, 4, 4>();

		m[0][0] = x;
		m[1][1] = y;
		m[2][2] = z;

		return m;
	}

	template<typename T>
	constexpr Matrix<T, 4, 4> scale(T s)
	{
		return scale(s, s, s);
	}
}

#endif // !MATHLIB_TRANSFORMS_H
