#include "week3.hpp"

#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>
#include <videolib/shapes/rectangle.hpp>

#include "src/camera.hpp"
#include "src/model.hpp"

ml::Vector<float, 2> dragOrigin;

Camera camera;

void drawModel(vl::Renderer& r, ml::Matrix<float, 3, 3> vp, Model m)
{
	std::vector<vl::Line> lines;

	for (int i = 0; i < m.vertices.size(); ++i) {
		const auto& a = m.vertices[i];
		const auto& b = m.vertices[(i + 1) % m.vertices.size()];

		const auto aTransformed = vp * m.modelM * ml::Vector<float, 3> { a[0], a[1], 1.0f };
		const auto bTransformed = vp * m.modelM * ml::Vector<float, 3> { b[0], b[1], 1.0f };

		lines.push_back({ aTransformed[0], aTransformed[1], bTransformed[0], bTransformed[1] });
	}

	r.drawLines(lines);
}

int main(int argc, char* args[])
{
	camera.left = -10.0f;
	camera.right = 10.0f;
	camera.top = 10.0f;
	camera.bottom = -10.0f;

	vl::Window window { "LINAL Week3", 640, 480 };
	vl::Instance instance { window };

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::right) ++camera.position[0];
		if (k == vl::Key::left) --camera.position[0];
		if (k == vl::Key::down) --camera.position[1];
		if (k == vl::Key::up) ++camera.position[1];
	});

	instance.onMouseDown([&](float x, float y) {
		dragOrigin = { x, y };
	});

	instance.onMouseHold([&](float x, float y) {
		ml::Vector<float, 3> diff { x - dragOrigin[0], y - dragOrigin[1], 1.0f };

		//auto newPos = ml::inverse(projection) * diff;

		camera.position[0] -= diff[0] * (camera.right - camera.left) / 2;
		camera.position[1] -= diff[1] * (camera.top - camera.bottom) / 2;
		dragOrigin = { x, y };
	});

	instance.onMouseScroll([&](float x, float y) {
		int zoom = std::ceil(y);

		camera.bottom -= zoom;
		camera.top += zoom;
		camera.left -= zoom;
		camera.right += zoom;
	});

	std::vector<ml::Vector<float, 2>> axisVertices { 2 };
	Model quad;
	quad.modelM[2][0] = 2.0f;
	quad.modelM[2][1] = 2.0f;
	quad.modelM[0][0] = 2.0f;
	quad.modelM[1][1] = 2.0f;
	quad.vertices = {
		{ -1.0f,  1.0f },
		{  1.0f,  1.0f },
		{  1.0f, -1.0f },
		{ -1.0f, -1.0f }
	};

	return instance.run([&](vl::Renderer& r) {
		r.viewport(-1.0f, 1.0f, 1.0f, -1.0f);
		r.clear();

		auto projection = camera.ortho();
		auto view = ml::identity<float, 3, 3>();
		view[2][0] = -camera.position[0];
		view[2][1] = -camera.position[1];

		const auto vp = projection * view;

		std::vector<ml::Vector<float, 2>> tmp { axisVertices };
		for (auto& v : tmp) {
			auto u = vp * ml::Vector<float, 3> { v[0], v[1], 1.0f };

			v = { u[0], u[1] };
		}

		r.color(255, 255, 255);
		r.drawLine({ -1.0f, tmp[0][1], 1.0f, tmp[1][1] });
		r.drawLine({ tmp[0][0], -1.0f, tmp[1][0], 1.0f });

		float size = 0.015f;

		for (int i = 0; i < 20; ++i) {
			r.drawLine({ tmp[0][0] + ((float)i / camera.right), tmp[0][1] + size, tmp[1][0] + ((float)i / camera.right), tmp[1][1] - size });
			r.drawLine({ tmp[0][0] + ((float)i / camera.left), tmp[0][1] + size, tmp[1][0] + ((float)i / camera.left), tmp[1][1] - size });
		}
		for (int i = 0; i < 20; ++i) {
			r.drawLine({ tmp[0][0] + size, tmp[0][1] + ((float)i / camera.top), tmp[1][0] - size, tmp[1][1] + ((float)i / camera.top) });
			r.drawLine({ tmp[0][0] + size, tmp[0][1] + ((float)i / camera.bottom), tmp[1][0] - size, tmp[1][1] + ((float)i / camera.bottom) });
		}

		r.color(255, 0, 0);
		drawModel(r, vp, quad);
	});
}
