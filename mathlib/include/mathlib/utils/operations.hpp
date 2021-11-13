#pragma once

#ifndef MATHLIB_OPERATIONS_H
#define MATHLIB_OPERATIONS_H

#include <cmath>

#include "../matrix.hpp"
#include "../vector.hpp"

namespace ml {
	const double pi = std::atan(1) * 4;

	constexpr double radians(double a)
	{
		return (a / 180.0) * pi;
	}

	template<typename T>
	constexpr T determinant(const Matrix<T, 2, 2>& m)
	{
		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	}
	template<typename T>
	constexpr T determinant(const Matrix<T, 3, 3>& m)
	{
		ml::Matrix<float, 2, 2> m1 { ml::Vector<float, 2>
			{ m[1][1], m[1][2] },
			{ m[2][1], m[2][2] }
		};
		ml::Matrix<float, 2, 2> m2 { ml::Vector<float, 2>
			{ m[0][1], m[0][2] },
			{ m[2][1], m[2][2] }
		};
		ml::Matrix<float, 2, 2> m3 { ml::Vector<float, 2>
			{ m[0][1], m[0][2] },
			{ m[1][1], m[1][2] }
		};

		return m[0][0] * ml::determinant(m1)
			 - m[1][0] * ml::determinant(m2)
			 + m[2][0] * ml::determinant(m3);
	}

	template<typename T, size_t N>
	constexpr float dot(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Matrix<T, N, 1> m { a };

		return ml::transpose(m) * b;
	}

	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, M, N> identity()
	{
		Matrix<T, M, N> m;

		for (int i = 0; i < N; ++i) {
			m[i][i] = static_cast<T>(1);
		}

		return m;
	}

	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, M, N> inverse(const Matrix<T, N, M>& a)
	{
		Matrix<T, M, N> m;



		return m;
	}

	template<typename T, size_t N, size_t M>
	constexpr Matrix<T, M, N> transpose(const Matrix<T, N, M>& a)
	{
		Matrix<T, M, N> m;

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				m[i][j] = a[j][i];
			}
		}

		return m;
	}
}

#endif // !MATHLIB_OPERATIONS_H
