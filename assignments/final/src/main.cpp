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

	ml::Vector<float, 2> h1 { -1.0f,  0.0f };
	ml::Vector<float, 2> h2 {  1.0f,  0.0f };
	ml::Vector<float, 2> v1 {  0.0f, -1.0f };
	ml::Vector<float, 2> v2 {  0.0f,  1.0f };

	std::vector<ml::Vector<float, 2>> vertices {
		{ -1.0f,  0.0f },
		{  1.0f,  0.0f },
		{  0.0f, -1.0f },
		{  0.0f,  1.0f }
	};

	vl::Line h { h1[0], h1[1], h2[0], h2[1] };
	vl::Line v { v1[0], v1[1], v2[0], v2[1] };

	float speed = 0.1;

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::l) camera[0] += speed;
		if (k == vl::Key::h) camera[0] -= speed;
		if (k == vl::Key::j) camera[1] -= speed;
		if (k == vl::Key::k) camera[1] += speed;

		std::cout << camera[0] << ", " << camera[1] << std::endl;
	});

	return instance.run([&](vl::Renderer& r) {
		r.clear();

		auto view = ml::identity<float, 3, 3>();
		view[2][0] = -camera[0];
		view[2][1] = -camera[1];

		std::vector<ml::Vector<float, 2>> tmp { vertices };
		for (auto& v : tmp) {
			auto u = view * ml::Vector<float, 3> { v[0], v[1], 1.0f };

			v = { u[0], u[1] };
		}

		r.color(255, 255, 255);
		r.drawLine({ -1.0f, tmp[0][1], 1.0f, tmp[1][1] });
		r.drawLine({ tmp[2][0], -1.0f, tmp[3][0], 1.0f });
	});
}
