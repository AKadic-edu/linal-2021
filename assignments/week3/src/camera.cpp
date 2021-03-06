#include "src/camera.hpp"

#include <mathlib/utils/operations.hpp>

ml::Matrix<float, 3, 3> Camera::ortho(float aspect) const
{
	auto m = ml::identity<float, 3, 3>();

	m[0][0] = 2 / ((right - left) * aspect);
	m[1][1] = 2 / (top - bottom);

	return m;
}
