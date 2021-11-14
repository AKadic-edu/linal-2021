#pragma once

#ifndef VIDEOLIB_RENDERER_HPP
#define VIDEOLIB_RENDERER_HPP

#include <vector>

#include <mathlib/vector.hpp>

struct SDL_Renderer;

namespace vl {
	struct Line;
	struct Window;

	class Renderer {
	public:
		Renderer(SDL_Renderer&, const Window&);
		Renderer(Renderer const&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer const&) = delete;
		Renderer& operator=(Renderer&&) = delete;
		virtual ~Renderer() = default;

		void clear(int = 0, int = 0, int = 0, int = 255);
		void color(int, int, int, int = 255);
		void viewport(float x1, float y1, float x2, float y2);

		void drawLine(const Line&);
		void drawLines(const std::vector<Line>&);
	private:
		const Window& m_window;
		SDL_Renderer& m_rendererHandle;
		ml::Vector<float, 2> m_viewport[2];
	};
}

#endif // !VIDEOLIB_RENDERER_HPP
