#include "week2.hpp"

#include <videolib/instance.hpp>
#include <videolib/key.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

int g_xSteps { 20 };
int g_ySteps { 20 };

float g_xSlope { 1.0f / g_xSteps };
float g_ySlope { 1.0f / g_ySteps };

vl::Line g_hAxis { -1.0f, 0, 1.0f, 0 };
vl::Line g_vAxis { 0, -1.0f, 0, 1.0f };

int g_grey { 200 };

void drawAxis(vl::Renderer& renderer)
{
	renderer.setColor(0, 0, 0);
	renderer.drawLine(g_hAxis);
	renderer.drawLine(g_vAxis);
}

void drawGrid(vl::Renderer& renderer)
{
	renderer.setColor(g_grey, g_grey, g_grey);

	for (int i { -g_xSteps }; i < g_xSteps; i+=2) {
		float offset { i * g_xSlope };

		vl::Line l { offset, -1, offset, 1 };

		renderer.drawLine(l);
	}
	for (int i { -g_ySteps }; i < g_ySteps; i += 2) {
		float offset { i * g_ySlope };

		vl::Line l { -1, offset, 1, offset };

		renderer.drawLine(l);
	}
}

void drawVector(vl::Renderer& renderer, const ml::Vector<float, 2>& v)
{
	vl::Line l { 0.0f, 0.0f, v[0] / (g_xSteps / 2), v[1] / (g_ySteps / 2) };

	renderer.drawLine(l);
}

int main(int argc, char* argv[])
{
	vl::Window window { 640, 480 };
	vl::Instance instance { window };

	ml::Vector<float, 2> vector { 0.0f, 0.0f };

	instance.onMouseMove([&](float x, float y) {
		vector[0] = x * g_xSteps / 2;
		vector[1] = y * g_xSteps / 2;
	});

	return instance.run([&](vl::Renderer& renderer) {
		renderer.clear(255, 255, 255);

		drawGrid(renderer);
		drawAxis(renderer);

		renderer.setColor(255, 0, 0);
		drawVector(renderer, vector);
	});
}
