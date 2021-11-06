#pragma once

#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H

#include "vector.hpp"

namespace ml {
	template <typename T, size_t N, size_t M>
	struct Matrix {
		Vector<T, N> m[M];

		constexpr Vector<T, N>& operator[](size_t index)
		{
			return m[index];
		}
		constexpr const Vector<T, N>& operator[](size_t index) const
		{
			return m[index];
		}
	};

	template<typename T, typename U, size_t N, size_t M>
	constexpr Vector<T, N> operator*(const Matrix<T, N, M>& a, const Vector<U, N>& b)
	{
		Vector<T, N> out;

		for (auto i { 0 }; i < M; ++i) {
			for (auto j { 0 }; j < N; ++j) {
				out[i] += a[j][i] * static_cast<T>(b[j]);
			}
		}

		return out;
	}
}

#endif // !MATHLIB_MATRIX_H
