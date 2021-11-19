#include "src/camera.hpp"

#include <mathlib/utils/operations.hpp>
#include <mathlib/utils/helpers.hpp>

ml::Matrix<float, 3, 3> ortho(const Camera<2>& c, float aspect)
{
	auto m = ml::identity<float, 3, 3>();

	m[0][0] = 2 / ((c.right - c.left) * aspect);
	m[1][1] = 2 / (c.top - c.bottom);

	return m;
}

ml::Matrix<float, 4, 4> ortho(const Camera<3>& c, float aspect)
{
	auto m = ml::identity<float, 4, 4>();

	m[0][0] = 2 / ((c.right - c.left) * aspect);
	m[1][1] = 2 / (c.top - c.bottom);

	return m;
}

ml::Matrix<float, 3, 3> view(const Camera<2>& c)
{
	auto m = ml::identity<float, 3, 3>();

	m[2][0] = -c.position[0];
	m[2][1] = -c.position[1];

	return m;
}

ml::Matrix<float, 4, 4> view(const Camera<3>& c)
{
	auto m = ml::identity<float, 4, 4>();

	m[3][0] = -c.position[0];
	m[3][1] = -c.position[1];
	m[3][2] = -c.position[2];

	return m;
}