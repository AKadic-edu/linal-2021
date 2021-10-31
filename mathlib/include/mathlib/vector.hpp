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
		constexpr const T& operator[](int index) const
		{
			return v[index];
		}
		constexpr Vector operator-(Vector& a) const
		{
			Vector out;

			for (int i { 0 }; i < N; ++i) {
				out[i] = v[i] - a[i];
			}

			return out;
		}
		constexpr Vector operator*(Vector<float, N>& a) const
		{
			Vector out;

			for (int i{ 0 }; i < N; ++i) {
				out[i] = v[i] * static_cast<T>(a[i]);
			}

			return out;
		}
		constexpr Vector operator*(Vector<int, N>& a) const
		{
			Vector out;

			for (int i{ 0 }; i < N; ++i) {
				out[i] = v[i] * static_cast<T>(a[i]);
			}

			return out;
		}
		constexpr Vector operator*(int a) const
		{
			Vector out;

			for (int i{ 0 }; i < N; ++i) {
				out[i] = v[i] * a;
			}

			return out;
		}
		constexpr Vector operator/(int a) const
		{
			Vector out;

			for (int i{ 0 }; i < N; ++i) {
				out[i] = v[i] / a;
			}

			return out;
		}
	};

	template<typename T, int N>
	constexpr Vector<T, N> operator+(T a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (int i{ 0 }; i < N; ++i) {
			out[i] = a + static_cast<T>(b[i]);
		}

		return out;
	}
	template<typename T, int N>
	constexpr Vector<T, N> operator+(const Vector<T, N>& a, T b)
	{
		Vector<T, N> out;

		for (int i{ 0 }; i < N; ++i) {
			out[i] = a[i] + static_cast<T>(b);
		}

		return out;
	}
	template<typename T, int N>
	constexpr Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (int i{ 0 }; i < N; ++i) {
			out[i] = a[i] + static_cast<T>(b[i]);
		}

		return out;
	}
	template<typename T, typename S, int N>
	constexpr Vector<T, N> operator+(const Vector<T, N>& a, const Vector<S, N>& b)
	{
		Vector<T, N> out;

		for (int i{ 0 }; i < N; ++i) {
			out[i] = a[i] + static_cast<T>(b[i]);
		}

		return out;
	}

	template<typename T, int N>
	constexpr Vector<T, N> operator*(T a, const Vector<T, N>& b)
	{
		Vector<T, N> out;

		for (int i{ 0 }; i < N; ++i) {
			out[i] = b[i] * static_cast<T>(a);
		}

		return out;
	}
}

#endif // !MATHLIB_VECTOR_H
