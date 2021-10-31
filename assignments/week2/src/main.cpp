#include "week2.hpp"

#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

int g_xSteps { 2 };
int g_ySteps { 2 };

void drawGrid(vl::Window& window, vl::Renderer& renderer)
{
	float xSlope { 1.0f / g_xSteps };
	float ySlope { 1.0f / g_ySteps };

	for (int i { -g_xSteps }; i < g_xSteps; ++i) {
		float offset { i * xSlope };

		vl::Line l { offset, -1, offset, 1 };

		renderer.drawLine(l);
	}
	for (int i { -g_ySteps }; i < g_ySteps; ++i) {
		float offset { i * ySlope };

		vl::Line l { -1, offset, 1, offset };

		renderer.drawLine(l);
	}

	for (int i{ 0 }; i < g_ySteps; ++i) {
		int offset { static_cast<int>(i * ySlope) };

		vl::Line l { 0, offset, window.width, offset };

		renderer.drawLine(l);
	}
}

int main(int argc, char* argv[])
{
	//vl::Rectangle rect { 0, 0, 50, 50 };
	vl::Window window { 640, 480 };
	vl::Instance instance { window };

	vl::Line hAxis { -1.0f, 0, 1.0f, 0 };
	vl::Line vAxis { 0, -1.0f, 0, 1.0f };

	return instance.run([&](vl::Renderer& renderer) {
		renderer.setColor(255, 255, 255);
		renderer.clear();

		int grey { 200 };
		renderer.setColor(grey, grey, grey);
		drawGrid(window, renderer);

		renderer.setColor(0, 0, 0);
		renderer.drawLine(hAxis);
		renderer.drawLine(vAxis);
	});
}
