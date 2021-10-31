#pragma once

#ifndef VIDEOLIB_RENDERER_HPP
#define VIDEOLIB_RENDERER_HPP

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

		void clear();
		void drawLine(const Line&);
		void setColor(int, int, int, int = 255);
	private:
		SDL_Renderer& m_rendererHandle;
		const Window& m_window;
	};
}

#endif // !VIDEOLIB_RENDERER_HPP