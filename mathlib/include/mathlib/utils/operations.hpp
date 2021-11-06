#pragma once

#ifndef MATHLIB_OPERATIONS_H
#define MATHLIB_OPERATIONS_H

#include "../matrix.hpp"
#include "../vector.hpp"

namespace ml {
	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, M, N> transpose(const Matrix<T, N, M>& m)
	{
		Matrix<T, M, N> out;

		for (auto i { 0 }; i < N; ++i) {
			for (auto j { 0 }; j < M; ++j) {
				out[i][j] = m[j][i];
			}
		}

		return out;
	}

	template<typename T, size_t N>
	constexpr float dot(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Matrix<T, N, 1> m { a };

		return transpose(m) * b;
	}
}

#endif // !MATHLIB_OPERATIONS_H
