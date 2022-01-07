#include "include/videolib/renderer.hpp"

#include "videolib.hpp"

#include "include/videolib/model.hpp"
#include "include/videolib/window.hpp"
#include "include/videolib/shapes/line.hpp"
#include "include/videolib/shapes/rectangle.hpp"
#include "src/videolib/utils/coordinate_helper.hpp"

vl::Renderer::Renderer(SDL_Renderer& rendererHandle, const Window& window)
    : m_rendererHandle { rendererHandle }
    , m_window { window }
    , m_debug { false }
{
    viewport(-1.0f, 1.0f, 1.0f, -1.0f);
}

void vl::Renderer::clear(int r, int g, int b, int a)
{
    color(r, g, b, a);
    SDL_Rect rect;
    rect.x = m_viewport[0][0];
    rect.y = m_viewport[0][1];
    rect.w = m_viewport[1][0];
    rect.h = m_viewport[1][1];
    SDL_RenderFillRect(&m_rendererHandle, &rect);
}

void vl::Renderer::color(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(&m_rendererHandle, r, g, b, a);
}

void vl::Renderer::debug(bool d)
{
    m_debug = d;
}

void vl::Renderer::viewport(float x1, float y1, float x2, float y2)
{
    m_viewport[0] = CoordinateHelper::toPixels({ m_window.width, m_window.height }, { x1, y1 });
    m_viewport[1] = CoordinateHelper::toPixels({ m_window.width, m_window.height }, { x2, y2 });
}

void vl::Renderer::drawLine(const Line& l)
{
    auto window = ml::Vector<int, 2> { m_window.width, m_window.height };
    auto from = convert({ l.x1, l.y1 });
    auto to = convert({ l.x2, l.y2 });

    SDL_RenderDrawLine(&m_rendererHandle, from[0], from[1], to[0], to[1]);
}

void vl::Renderer::drawLines(const std::vector<Line>& lines)
{
    std::vector<std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>>> points2d;

    std::transform(lines.begin(), lines.end(), std::back_inserter(points2d),
        [](Line l) -> std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>> {
            return std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>> { { l.x1, l.y1 }, { l.x2, l.y2 } };
        });

    std::vector<SDL_Point> points;

    for (const auto& v : points2d) {
        auto from = convert(std::get<0>(v));
        auto to = convert(std::get<1>(v));

        points.push_back({ from[0], from[1] });
        points.push_back({ to[0], to[1] });
    }

    const size_t count { lines.size() * 2 };

    SDL_RenderDrawLines(&m_rendererHandle, points.data(), static_cast<int>(count));
}

void vl::Renderer::drawModel(ml::Matrix<float, 4, 4> vp, const Model& m)
{
    std::vector<vl::Line> lines;

    for (int i = 0; i < m.vertices.size(); ++i) {
        const auto& a = m.vertices[i];
        const auto& b = m.vertices[(i + 1) % m.vertices.size()];

        const auto aTransformed = vp * m.worldM * m.modelM * ml::Vector<float, 4> { a[0], a[1], a[2], 1.0f };
        const auto bTransformed = vp * m.worldM * m.modelM * ml::Vector<float, 4> { b[0], b[1], b[2], 1.0f };

        if (aTransformed[3] < 0 || bTransformed[3] < 0) break;

        const ml::Vector<float, 2> aClipped{ aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] };
        const ml::Vector<float, 2> bClipped{ bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] };

        lines.push_back({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
    }

    drawLines(lines);

    if (m_debug) {
        color(255, 0, 0);
        drawVector(vp * m.worldM * m.modelM, { 1.0f, 0.0f, 0.0f });
        color(0, 255, 0);
        drawVector(vp * m.worldM * m.modelM, { 0.0f, 1.0f, 0.0f });
        color(0, 0, 255);
        drawVector(vp * m.worldM * m.modelM, { 0.0f, 0.0f, 1.0f });
    }
}

void vl::Renderer::drawVector(ml::Matrix<float, 4, 4> vp, ml::Vector<float, 3> vector)
{
    const auto aTransformed = vp * ml::Vector<float, 4> {  vector[0], vector[1], vector[2], 1.0f };
    const auto bTransformed = vp * ml::Vector<float, 4> { 0.0f, 0.0f, 0.0f, 1.0f };

    if (aTransformed[3] < 0 || bTransformed[3] < 0) return;

    const ml::Vector<float, 2> aClipped{ aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] };
    const ml::Vector<float, 2> bClipped{ bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] };

    drawLine({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
}

ml::Vector<int, 2> vl::Renderer::convert(const ml::Vector<float, 2>& v) const
{
    return m_viewport[0] + CoordinateHelper::toPixels(m_viewport[1] - m_viewport[0], v);
}
