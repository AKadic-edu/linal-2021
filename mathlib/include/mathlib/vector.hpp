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
		constexpr bool operator==(Vector a) const
		{
			for (size_t i { 0 }; i < N; ++i) {
				if (v[i] != a[i]) {
					return false;
				}
			}

			return true;
		}
		constexpr void operator+=(Vector a)
		{
			for (size_t i { 0 }; i < N; ++i) {
				v[i] += a[i];
			}
		}
		template<typename S>
		constexpr operator Vector<S, N>() const
		{
			Vector<S, N> out;

			for (size_t i { 0 }; i < N; ++i) {
				out[i] = static_cast<S>(v[i]);
			}

			return out;
		}
	};

	template<typename T, size_t N>
	constexpr Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (size_t i { 0 }; i < N; ++i) {
			out[i] = a[i] + b[i];
		}

		return out;
	}
	template<typename T, size_t N>
	constexpr Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (size_t i { 0 }; i < N; ++i) {
			out[i] = a[i] - b[i];
		}

		return out;
	}
	template<typename T, size_t N>
	constexpr Vector<T, N> operator*(T scalar, const Vector<T, N>& v)
	{
		Vector<T, N> out;

		for (size_t i{ 0 }; i < N; ++i) {
			out[i] = scalar * v[i];
		}

		return out;
	}
}

#endif // !MATHLIB_VECTOR_H
