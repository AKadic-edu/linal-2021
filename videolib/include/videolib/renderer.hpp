#pragma once

#ifndef VIDEOLIB_RENDERER_HPP
#define VIDEOLIB_RENDERER_HPP

#include <vector>

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>

struct SDL_Renderer;

namespace vl {
	struct Line;
	struct Model;
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
		void debug(bool);
		void viewport(float x1, float y1, float x2, float y2);

		void drawLine(const Line&);
		void drawLines(const std::vector<Line>&);
		void drawModel(ml::Matrix<float, 4, 4> vp, const Model& m);
		void drawVector(ml::Matrix<float, 4, 4> vp, ml::Vector<float, 3> vector);
	private:
		bool m_debug;
		const Window& m_window;
		SDL_Renderer& m_rendererHandle;
		ml::Matrix<int, 2, 2> m_viewport;

		ml::Vector<int, 2> convert(const ml::Vector<float, 2>&) const;
	};
}

#endif // !VIDEOLIB_RENDERER_HPP
