#include "assessment.hpp"

#include <mathlib/matrix.hpp>
#include <mathlib/utils/operations.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

#include "src/camera.hpp"
#include "src/view.hpp"

struct Model {
	ml::Matrix<float, 3, 3> modelM { ml::identity<float, 3, 3>() };
	std::vector<ml::Vector<float, 2>> vertices;
};

ml::Vector<float, 2> clip(const ml::Vector<float, 2>& v)
{
	auto out = v;

	if (out[0] < -1.0f) out[0] = -1.0f;
	if (out[1] < -1.0f) out[1] = -1.0f;
	if (out[0] >  1.0f) out[0] =  1.0f;
	if (out[1] >  1.0f) out[1] =  1.0f;

	return out;
}

void drawModel(vl::Renderer& r, ml::Matrix<float, 3, 3> vp, Model m)
{
	std::vector<vl::Line> lines;

	for (int i = 0; i < m.vertices.size(); ++i) {
		const auto& a = m.vertices[i];
		const auto& b = m.vertices[(i + 1) % m.vertices.size()];

		const auto aTransformed = vp * m.modelM * ml::Vector<float, 3> { a[0], a[1], 1.0f };
		const auto bTransformed = vp * m.modelM * ml::Vector<float, 3> { b[0], b[1], 1.0f };

		const auto aClipped = clip({ aTransformed[0], aTransformed[1] });
		const auto bClipped = clip({ bTransformed[0], bTransformed[1] });

		lines.push_back({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
	}

	r.drawLines(lines);
}

int main(int argc, char* args[])
{
	vl::Window window { "LINAL Assessment", 640, 480 };
	vl::Instance instance { window };

	Model quad;
	quad.vertices = {
		{ -1.0f,  1.0f },
		{  1.0f,  1.0f },
		{  1.0f, -1.0f },
		{ -1.0f, -1.0f }
	};

	View topView { -1.0f, 1.0f, 0.0f, 0.0f };
	View sideView { 0.0f, 1.0f, 1.0f, 0.0f };
	View frontView { -1.0f, 0.0f, 1.0f, -1.0f };

	Camera cam;
	cam.left = -10.0f;
	cam.right = 10.0f;
	cam.top = 10.0f;
	cam.bottom = -10.0f;

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::right) ++cam.position[0];
		if (k == vl::Key::left) --cam.position[0];
		if (k == vl::Key::down) --cam.position[1];
		if (k == vl::Key::up) ++cam.position[1];
	});

	instance.onMouseScroll([&](float x, float y) {
		int zoom = std::ceil(y);

		cam.bottom -= zoom;
		cam.top += zoom;
		cam.left -= zoom;
		cam.right += zoom;
	});

	return instance.run([&](vl::Renderer& r) {
		const auto projection = cam.ortho((float)window.width / window.height);
		const auto view = cam.view();

		topView.draw(r, [&](vl::Renderer& r) {
			r.clear(255, 255, 255);
			r.color(0, 0, 0);
			drawModel(r, projection * view, quad);
		});

		sideView.draw(r, [&](vl::Renderer& r) {
			r.clear(255, 255, 255);
			r.color(0, 0, 0);
			drawModel(r, projection * view, quad);
		});

		frontView.draw(r, [&](vl::Renderer& r) {
			const auto frontViewProjection = cam.ortho((float)window.width * 2 / window.height);

			r.clear(255, 255, 255);
			r.color(0, 0, 0);
			drawModel(r, frontViewProjection * view, quad);
		});

		r.color(0, 0, 0);
		r.drawLine({ -1.0f, 0.0f, 1.0f, 0.0f });
		r.drawLine({ 0.0f, 0.0f, 0.0f, 1.0f });
	});
}
