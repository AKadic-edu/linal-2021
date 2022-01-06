#pragma once

#ifndef VIEW_HPP
#define VIEW_HPP

#include "assessment.hpp"

namespace vl {
	class Renderer;
}

class View {
public:
	View(
		float x1 = -1.0f,
		float y1 = -1.0f,
		float x2 =  1.0f,
		float y2 =  1.0f);

	void draw(vl::Renderer&, std::function<void(vl::Renderer&)>) const;
private:
	float m_x1, m_y1;
	float m_x2, m_y2;
	ml::Matrix<float, 2, 2> m_viewport;
};

#endif // !VIEW_HPP
