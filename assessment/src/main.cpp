#include "assessment.hpp"

#include <mathlib/matrix.hpp>
#include <mathlib/utils/operations.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

struct Model {
	ml::Matrix<float, 3, 3> modelM { ml::identity<float, 3, 3>() };
	std::vector<ml::Vector<float, 2>> vertices;
};

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
	vl::Window window { "LINAL Assessment", 640, 480 };
	vl::Instance instance { window };

	Model quad;
	quad.modelM[0][0] = 0.5f;
	quad.modelM[1][1] = 0.5f;
	quad.vertices = {
		{ -1.0f,  1.0f },
		{  1.0f,  1.0f },
		{  1.0f, -1.0f },
		{ -1.0f, -1.0f }
	};

	return instance.run([&](vl::Renderer& r) {
		r.viewport(-1.0f, 1.0f, 0.0f, 0.0f);
		r.clear(255, 0, 0);
		r.color(255, 255, 255);
		drawModel(r, ml::identity<float, 3, 3>(), quad);

		r.viewport(0.0f, 1.0f, 1.0f, 0.0f);
		r.clear(0, 255, 0);
		r.color(255, 255, 255);
		drawModel(r, ml::identity<float, 3, 3>(), quad);

		r.viewport(-1.0f, 0.0f, 1.0f, -1.0f);
		r.clear(0, 0, 255);
		r.color(255, 255, 255);
		drawModel(r, ml::identity<float, 3, 3>(), quad);
	});
}
