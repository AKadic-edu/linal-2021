#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>
#include <videolib/shapes/rectangle.hpp>

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
		ml::Vector<float, 3> diff { x - dragOrigin[0], y - dragOrigin[1], 1.0f };

		//auto newPos = ml::inverse(scale) * diff;

		camera[0] += diff[0] * width;
		camera[1] += diff[1] * height;
		dragOrigin = { x, y };
	});

	instance.onMouseScroll([&](float x, float y) {
	});

	return instance.run([&](vl::Renderer& r) {
		r.clear();

		auto scaleM = ml::identity<float, 3, 3>();
		scaleM[0][0] = 1.0f / width;
		scaleM[1][1] = 1.0f / height;

		auto translationM = ml::identity<float, 3, 3>();
		translationM[2][0] = camera[0];
		translationM[2][1] = camera[1];

		std::vector<ml::Vector<float, 2>> tmp { vertices };
		for (auto& v : tmp) {
			auto u = scaleM * translationM * ml::Vector<float, 3> { v[0], v[1], 1.0f };

			v = { u[0], u[1] };
		}

		r.color(255, 255, 255);
		r.drawLine({ -1.0f, tmp[0][1], 1.0f, tmp[1][1] });
		r.drawLine({ tmp[0][0], -1.0f, tmp[1][0], 1.0f });

		auto pos = scaleM * translationM * ml::Vector<float, 3> { 0.0f, 0.0f, 1.0f };
		auto size = scaleM * ml::Vector<float, 3> { 1.0f, 1.0f, 1.0f };

		r.color(255, 0, 0);
		r.drawRectangle({ pos[0], pos[1], size[0], size[1] });
	});
}
