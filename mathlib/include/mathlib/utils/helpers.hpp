#pragma once

#ifndef MATHLIB_HELPERS_H
#define MATHLIB_HELPERS_H

#include "../matrix.hpp"

namespace ml {
	template<typename T, size_t N, size_t M, size_t K, size_t L>
	constexpr Matrix<T, N, M> copy(const Matrix<T, N, M>& a, const Matrix<T, K, L>& b)
	{
		Matrix<T, M, N> m;

		for (int i = 0; i < K; ++i) {
			for (int j = 0; j < L; ++j) {
				m[i][j] = (T)b[i][j];
			}
		}

		return m;
	}
}

#endif // !MATHLIB_HELPERS_H
