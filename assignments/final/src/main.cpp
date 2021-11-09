#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>
#include <videolib/shapes/rectangle.hpp>

#include <iostream>

ml::Vector<float, 2> dragOrigin;

float left   = -10.0f;
float right  =  10.0f;
float top	 =  10.0f;
float bottom = -10.0f;

ml::Matrix<float, 3, 3> ortho()
{
	auto m = ml::identity<float, 3, 3>();
	m[0][0] = 2 / (right - left);
	m[1][1] = 2 / (top - bottom);

	return m;
}

int main()
{
	vl::Window window { "LINAL Final", 640, 480 };
	vl::Instance instance { window };

	ml::Vector<float, 2> camera { 0.0f, 0.0f };

	std::vector<ml::Vector<float, 2>> vertices { 2 };

	auto projection = ortho();

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::right) ++camera[0];
		if (k == vl::Key::left) --camera[0];
		if (k == vl::Key::down) --camera[1];
		if (k == vl::Key::up) ++camera[1];
	});

	instance.onMouseDown([&](float x, float y) {
		dragOrigin = { x, y };
	});

	instance.onMouseHold([&](float x, float y) {
		ml::Vector<float, 3> diff{ x - dragOrigin[0], y - dragOrigin[1], 1.0f };

		//auto newPos = ml::inverse(projection) * diff;

		camera[0] -= diff[0] * (right - left) / 2;
		camera[1] -= diff[1] * (top - bottom) / 2;
		dragOrigin = { x, y };
	});

	return instance.run([&](vl::Renderer& r) {
		r.clear();

		auto view = ml::identity<float, 3, 3>();
		view[2][0] = -camera[0];
		view[2][1] = -camera[1];

		std::vector<ml::Vector<float, 2>> tmp { vertices };
		for (auto& v : tmp) {
			auto u = projection * view * ml::Vector<float, 3> { v[0], v[1], 1.0f };

			v = { u[0], u[1] };
		}

		r.color(255, 255, 255);
		r.drawLine({ -1.0f, tmp[0][1], 1.0f, tmp[1][1] });
		r.drawLine({ tmp[0][0], -1.0f, tmp[1][0], 1.0f });
	});
}
