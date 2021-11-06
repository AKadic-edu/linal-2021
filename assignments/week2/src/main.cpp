#include "week2.hpp"

#include <mathlib/matrix.hpp>
#include <videolib/shapes/line.hpp>
#include <videolib/shapes/rectangle.hpp>
#include <videolib/instance.hpp>
#include <videolib/key.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>

int g_xSteps { 10 };
int g_ySteps { 10 };

float g_xSlope { 1.0f / g_xSteps };
float g_ySlope { 1.0f / g_ySteps };

vl::Line g_hAxis { -1.0f, 0, 1.0f, 0 };
vl::Line g_vAxis { 0, -1.0f, 0, 1.0f };

int g_grey { 100 };

ml::Vector<float, 2> g_i { 1.0f, 0.0f };
ml::Vector<float, 2> g_j { 0.0f, 1.0f };
ml::Matrix<float, 2, 2> g_rotation { ml::Vector<float, 2>
	{  0.0f, 1.0f },
	{ -1.0f, 0.0f }
};
ml::Matrix<float, 2, 2> g_shear { ml::Vector<float, 2>
	{  1.0f, 0.0f },
	{  1.0f, 1.0f }
};
ml::Vector<float, 2> g_vector { 1.0f, 1.0f };
					 

void drawAxis(vl::Renderer& renderer)
{
	renderer.color(255, 255, 255);
	renderer.drawLine(g_hAxis);
	renderer.drawLine(g_vAxis);
}

void drawGrid(vl::Renderer& renderer)
{
	renderer.color(g_grey, g_grey, g_grey);

	std::vector<vl::Line> lines;

	for (int i { -g_xSteps }; i < g_xSteps; i+=2) {
		float offset { i * g_xSlope };

		lines.push_back({ offset, -1, offset, 1 });
	}
	for (int i { -g_ySteps }; i < g_ySteps; i += 2) {
		float offset { i * g_ySlope };

		lines.push_back({ -1, offset, 1, offset });
	}
	for (const auto& l : lines) {
		renderer.drawLine(l);
	}
}

void drawVector(vl::Renderer& renderer, const ml::Vector<float, 2>& v)
{
	vl::Line l { 0.0f, 0.0f, v[0] / (g_xSteps / 2), v[1] / (g_ySteps / 2) };

	renderer.drawLine(l);
}

void update()
{

}

void draw(vl::Renderer& renderer)
{
	renderer.clear();

	drawGrid(renderer);
	drawAxis(renderer);

	renderer.color(0, g_grey, 0);
	drawVector(renderer, g_i);
	renderer.color(g_grey, 0, 0);
	drawVector(renderer, g_j);

	renderer.color(g_grey, g_grey, 0);
	drawVector(renderer, g_vector);

	auto m = g_shear * g_rotation;

	renderer.color(0, 255, 0);
	drawVector(renderer, m * g_i);
	renderer.color(255, 0, 0);
	drawVector(renderer, m * g_j);

	renderer.color(255, 255, 0);
	drawVector(renderer, m * g_vector);
}

int main(int argc, char* argv[])
{
	vl::Window window { 640, 480 };
	vl::Instance instance { window };

	return instance.run([&](vl::Renderer& renderer) {
		draw(renderer);
	});
}
