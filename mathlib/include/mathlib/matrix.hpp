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
		constexpr bool operator==(Matrix a) const
		{
			for (int i = 0; i < M; ++i) {
				for (int j = 0; j< N; ++j) {
					if (m[i][j] != a[i][j]) {
						return false;
					}
				}
			}

			return true;
		}
	};

	template<typename T, size_t M>
	constexpr T operator*(const Matrix<T, 1, M>& a, const Vector<T, M>& b)
	{
		T out = 0;

		for (int i = 0; i < M; ++i) {
			out += a[0][i] * b[i];
		}

		return out;
	}
	template<typename T, size_t N, size_t M>
	constexpr Vector<T, N> operator*(const Matrix<T, N, M>& a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				out[i] += a[j][i] * b[j];
			}
		}

		return out;
	}
	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, N, M> operator*(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b)
	{
		Matrix<T, N, M> out;

		for (int i = 0; i < M; ++i) {
			out[i] = a * b[i];
		}

		return out;
	}
}

#endif // !MATHLIB_MATRIX_H
