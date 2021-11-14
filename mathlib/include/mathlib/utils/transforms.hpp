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

		rotationM[0][0] = (a == 90.0f || a == -90.0f) ? 0.0f : static_cast<float>(std::cos(radians(a)));
		rotationM[0][1] =  static_cast<float>(std::sin(radians(a)));
		rotationM[1][0] = -static_cast<float>(std::sin(radians(a)));
		rotationM[1][1] = (a == 90.0f || a == -90.0f) ? 0.0f : static_cast<float>(std::cos(radians(a)));

		return rotationM * m;
	}
}

#endif // !MATHLIB_TRANSFORMS_H
