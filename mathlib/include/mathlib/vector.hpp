#pragma once

#ifndef MATHLIB_VECTOR_H
#define MATHLIB_VECTOR_H

namespace ml {
	template<typename T, int N>
	struct Vector {
		T v[N] { 0 };

		constexpr T& operator[](int index)
		{
			return v[index];
		}

		constexpr Vector operator+(Vector& other) const
		{
			Vector out;

			for (int i { 0 }; i < N; ++i) {
				out[i] = v[i] + other[i];
			}

			return out;
		}

		constexpr Vector operator-(Vector& other) const
		{
			Vector out;

			for (int i { 0 }; i < N; ++i) {
				out[i] = v[i] - other[i];
			}

			return out;
		}
	};
}

#endif // !MATHLIB_VECTOR_H
