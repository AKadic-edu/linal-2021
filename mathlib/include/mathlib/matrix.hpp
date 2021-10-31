#pragma once

#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H

#include "vector.hpp"

namespace ml {
	template<typename T, int N, int M>
	struct Matrix {
		Vector<T, > m[];
	}
}

#endif // !MATHLIB_MATRIX_H
