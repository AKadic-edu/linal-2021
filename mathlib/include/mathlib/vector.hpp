#pragma once

#ifndef MATHLIB_VECTOR_H
#define MATHLIB_VECTOR_H

namespace ml {
	template<typename T, size_t N>
	struct Vector {
		T v[N] { 0 };

		constexpr T& operator[](size_t index)
		{
			return v[index];
		}
		constexpr const T& operator[](size_t index) const
		{
			return v[index];
		}
	};

	template<typename T, typename S, size_t N>
	constexpr Vector<T, N> operator+(const Vector<T, N>& a, const Vector<S, N>& b)
	{
		Vector<T, N> out;

		for (size_t i { 0 }; i < N; ++i) {
			out[i] = a[i] + static_cast<T>(b[i]);
		}

		return out;
	}
	template<typename T, typename S, size_t N>
	constexpr Vector<T, N> operator-(const Vector<T, N>& a, const Vector<S, N>& b)
	{
		Vector<T, N> out;

		for (size_t i { 0 }; i < N; ++i) {
			out[i] = a[i] - static_cast<T>(b[i]);
		}

		return out;
	}
	template<typename T, typename S, size_t N>
	constexpr Vector<T, N> operator*(T scalar, const Vector<S, N>& v)
	{
		Vector<T, N> out;

		for (size_t i { 0 }; i < N; ++i) {
			out[i] = scalar * static_cast<T>(v[i]);
		}

		return out;
	}
}

#endif // !MATHLIB_VECTOR_H
