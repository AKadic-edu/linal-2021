#include "assessment.hpp"

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

#include "src/camera.hpp"
#include "src/view.hpp"

float size = 2.0f;
float minSize =  1.0f;
float maxSize = 2.0f;
float animationSpeed = 0.002f;

float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
};

struct Model {
	ml::Matrix<float, 4, 4> modelM { ml::identity<float, 4, 4>() };
	std::vector<ml::Vector<float, 3>> vertices;
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

Model animate(Model m)
{
	if (m.modelM[0][0] < minSize || m.modelM[0][0] > maxSize) {
		animationSpeed = -animationSpeed;
	}

	m.modelM[0][0] += animationSpeed;
	m.modelM[1][1] += animationSpeed;
	m.modelM[2][2] += animationSpeed;

	return m;
}

void drawAxis(vl::Renderer& r, ml::Matrix<float, 4, 4> vp, ml::Vector<float, 3> basis)
{
	const auto aTransformed = vp * ml::Vector<float, 4> {  basis[0],  basis[1],  basis[2], 1.0f };
	const auto bTransformed = vp * ml::Vector<float, 4> { -basis[0], -basis[1], -basis[2], 1.0f };

	const auto aClipped = clip({ aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] });
	const auto bClipped = clip({ bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] });

	r.drawLine({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
}

void drawModel(vl::Renderer& r, ml::Matrix<float, 4, 4> vp, Model m)
{
	std::vector<vl::Line> lines;

	for (int i = 0; i < m.vertices.size(); ++i) {
		const auto& a = m.vertices[i];
		const auto& b = m.vertices[(i + 1) % m.vertices.size()];

		const auto aTransformed = vp * m.modelM * ml::Vector<float, 4> { a[0], a[1], a[2], 1.0f };
		const auto bTransformed = vp * m.modelM * ml::Vector<float, 4> { b[0], b[1], b[2], 1.0f };

		const auto aClipped = clip({ aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] });
		const auto bClipped = clip({ bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] });

		lines.push_back({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
	}

	r.drawLines(lines);
}

int main(int argc, char* args[])
{
	vl::Window window { "LINAL Assessment", 640, 480 };
	vl::Instance instance { window };

	Model quad;
	quad.modelM[0][0] = size;
	quad.modelM[1][1] = size;
	quad.modelM[2][2] = size;
	for (int i = 0; i < sizeof(vertices)/sizeof(*vertices); i += 3) {
		quad.vertices.push_back({ vertices[i], vertices[i + 1], vertices[i + 2] });
	}

	View topView { -1.0f, 1.0f, 0.0f, 0.0f };
	View sideView { 0.0f, 1.0f, 1.0f, 0.0f };
	View frontView { -1.0f, 0.0f, 1.0f, -1.0f };

	Camera<3> cam;
	cam.up = { 0.0f, 1.0f, 0.0f };
	cam.left = -10.0f;
	cam.right = 10.0f;
	cam.top = 10.0f;
	cam.bottom = -10.0f;
	Camera<3> topCam = cam;
	topCam.up = { 0.0f, 0.0f, 1.0f };
	topCam.position = { 0.0f, 3.0f, 0.0f };
	Camera<3> sideCam = cam;
	sideCam.position = { 3.0f, 0.0f, 0.0f };
	Camera<3> frontCam = cam;
	frontCam.position = { 0.0f, 0.0f, -3.0f };

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::right) ++quad.modelM[3][0];
		if (k == vl::Key::left) --quad.modelM[3][0];
		if (k == vl::Key::down) --quad.modelM[3][2];
		if (k == vl::Key::up) ++quad.modelM[3][2];
	});

	instance.onMouseScroll([&](float x, float y) {
		int zoom = (int)std::ceil(y);

		cam.bottom -= zoom;
		cam.top += zoom;
		cam.left -= zoom;
		cam.right += zoom;
	});

	float basis = 5.0f;

	return instance.run([&](vl::Renderer& r) {
		//quad = animate(quad);

		const auto projectionM = ortho(cam, (float)window.width / window.height);

		topView.draw(r, [&](vl::Renderer& r) {
			const auto viewM = view(topCam);
			auto vp = projectionM * viewM;

			r.clear(255, 255, 255);

			r.color(255, 0, 0);
			drawAxis(r, vp, { basis, 0.0f, 0.0f });
			r.color(0, 255, 0);
			drawAxis(r, vp, { 0.0f, basis, 0.0f });
			r.color(0, 0, 255);
			drawAxis(r, vp, { 0.0f, 0.0f, basis });

			r.color(0, 0, 0);
			drawModel(r, vp, quad);
		});

		sideView.draw(r, [&](vl::Renderer& r) {
			const auto viewM = view(sideCam);
			auto vp = projectionM * viewM;

			r.clear(255, 255, 255);

			r.color(255, 0, 0);
			drawAxis(r, vp, { basis, 0.0f, 0.0f });
			r.color(0, 255, 0);
			drawAxis(r, vp, { 0.0f, basis, 0.0f });
			r.color(0, 0, 255);
			drawAxis(r, vp, { 0.0f, 0.0f, basis });

			r.color(0, 0, 0);
			drawModel(r, vp, quad);
		});

		frontView.draw(r, [&](vl::Renderer& r) {
			const auto frontViewProjection = ortho(cam, (float)window.width * 2 / window.height);
			const auto viewM = view(frontCam);
			auto vp = frontViewProjection * viewM;

			r.clear(255, 255, 255);

			r.color(255, 0, 0);
			drawAxis(r, vp, { basis, 0.0f, 0.0f });
			r.color(0, 255, 0);
			drawAxis(r, vp, { 0.0f, basis, 0.0f });
			r.color(0, 0, 255);
			drawAxis(r, vp, { 0.0f, 0.0f, basis });

			r.color(0, 0, 0);
			drawModel(r, vp, quad);
		});

		r.color(0, 0, 0);
		r.drawLine({ -1.0f, 0.0f, 1.0f, 0.0f });
		r.drawLine({ 0.0f, 0.0f, 0.0f, 1.0f });
	});
}
