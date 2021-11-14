#include "src/view.hpp"

#include <videolib/renderer.hpp>

View::View(float x1, float y1, float x2, float y2)
	: m_x1 { x1 }
	, m_y1 { y1 }
	, m_x2 { x2 }
	, m_y2 { y2 }
{ }

void View::draw(vl::Renderer& r, std::function<void(vl::Renderer&)> cb) const
{
	r.viewport(m_x1, m_y1, m_x2, m_y2);
	cb(r);
	r.viewport(-1.0f, 1.0f, 1.0f, -1.0f);
}
