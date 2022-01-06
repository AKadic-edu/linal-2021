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

ml::Matrix<float, 4, 4> perspective(const Camera<3>& c, float far, float near, float fov)
{
	float s = near * std::tan((fov * 0.5f) * ml::pi / 180.0f);

	ml::Matrix<float, 4, 4> m;

	m[0][0] = s;
	m[1][1] = s;
	m[2][2] = -far / (far - near);
	m[2][3] = -far * near / (far - near);
	m[3][2] = -1.0f;

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
	auto forward = ml::normalize(c.position - c.target);
	auto right = ml::normalize(ml::cross(c.up, forward));
	auto up = ml::cross(forward, right);

	auto m = ml::identity<float, 4, 4>();

	m[0] = { right[0], right[1], right[2], 0.0f };
	m[1] = { up[0], up[1], up[2], 0.0f };
	m[2] = { forward[0], forward[1], forward[2], 0.0f };

	m = ml::transpose(m);

	auto n = ml::identity<float, 4, 4>();

	n[3][0] = -c.position[0];
	n[3][1] = -c.position[1];
	n[3][2] = -c.position[2];

	return m * n;
}
