#include <mathlib/utils/operations.hpp>
#include <mathlib/vector.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

#include <iostream>

int main()
{
	vl::Window window { "LINAL Final", 640, 480 };
	vl::Instance instance { window };

	ml::Vector<float, 2> camera { 0.0f, 0.0f };

	std::vector<ml::Vector<float, 2>> vertices { 2 };

	float speed = 1.0f;
	float width = 10.0f;
	float height = 10.0f;

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::l) camera[0] += speed;
		if (k == vl::Key::h) camera[0] -= speed;
		if (k == vl::Key::j) camera[1] -= speed;
		if (k == vl::Key::k) camera[1] += speed;
	});

	ml::Vector<float, 2> dragOrigin;

	instance.onMouseDown([&](float x, float y) {
		dragOrigin = { x, y };
	});

	instance.onMouseHold([&](float x, float y) {
		auto diffX = x - dragOrigin[0];
		auto diffY = y - dragOrigin[1];

		if (diffX == 0 && diffY == 0) return;

		camera[0] += -diffX * width;
		camera[1] += -diffY * height;
		dragOrigin = { x, y };
	});

	return instance.run([&](vl::Renderer& r) {
		r.clear();

		auto translation = ml::identity<float, 3, 3>();
		translation[2][0] = -camera[0];
		translation[2][1] = -camera[1];
		auto scale = ml::identity<float, 3, 3>();
		scale[0][0] = 1.0f / width;
		scale[1][1] = 1.0f / height;

		std::vector<ml::Vector<float, 2>> tmp { vertices };
		for (auto& v : tmp) {
			auto u = scale * translation * ml::Vector<float, 3> { v[0], v[1], 1.0f };

			v = { u[0], u[1] };
		}

		r.color(255, 255, 255);
		r.drawLine({ -1.0f, tmp[0][1], 1.0f, tmp[1][1] });
		r.drawLine({ tmp[0][0], -1.0f, tmp[1][0], 1.0f });
	});
}
