#include "include/videolib/renderer.hpp"

#include "videolib.hpp"

#include "include/videolib/shapes/line.hpp"
#include "include/videolib/shapes/rectangle.hpp"
#include "include/videolib/window.hpp"
#include "src/videolib/utils/coordinate_helper.hpp"

vl::Renderer::Renderer(SDL_Renderer& rendererHandle, const Window& window)
    : m_rendererHandle { rendererHandle }
    , m_window { window }
    , m_viewport { -1.0f, 1.0f, 1.0f, -1.0f }
{ }

void vl::Renderer::clear(int r, int g, int b, int a)
{
    auto absoluteViewportA = CoordinateHelper::toPixels({ m_window.width, m_window.height }, m_viewport[0]);
    auto absoluteViewportB = CoordinateHelper::toPixels({ m_window.width, m_window.height }, m_viewport[1]);

    color(r, g, b, a);
    SDL_Rect rect;
    rect.x = absoluteViewportA[0];
    rect.y = absoluteViewportA[1];
    rect.w = absoluteViewportB[0];
    rect.h = absoluteViewportB[1];
    SDL_RenderFillRect(&m_rendererHandle, &rect);
}

void vl::Renderer::color(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(&m_rendererHandle, r, g, b, a);
}

void vl::Renderer::viewport(float x1, float y1, float x2, float y2)
{
    m_viewport[0][0] = x1;
    m_viewport[0][1] = y1;
    m_viewport[1][0] = x2;
    m_viewport[1][1] = y2;
}

void vl::Renderer::drawLine(const Line& l)
{
    auto window = ml::Vector<int, 2> { m_window.width, m_window.height };
    auto from = CoordinateHelper::toPixels(window, { l.x1, l.y1 });
    auto to = CoordinateHelper::toPixels(window, { l.x2, l.y2 });

    SDL_RenderDrawLine(&m_rendererHandle, from[0], from[1], to[0], to[1]);
}

void vl::Renderer::drawLines(const std::vector<Line>& lines)
{
    const size_t count { lines.size() * 2 };
    const auto window = ml::Vector<int, 2>{ m_window.width, m_window.height };

    std::vector<std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>>> points2d;
    std::transform(lines.begin(), lines.end(), std::back_inserter(points2d),
        [](Line l) -> std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>> {
            return std::tuple<ml::Vector<float, 2>, ml::Vector<float, 2>> { { l.x1, l.y1 }, { l.x2, l.y2 } };
        });

    std::vector<SDL_Point> points;
    for (const auto& v : points2d) {
        const auto from = CoordinateHelper::toPixels(window, { std::get<0>(v)[0], std::get<0>(v)[1] });
        const auto to = CoordinateHelper::toPixels(window, { std::get<1>(v)[0], std::get<1>(v)[1] });

        points.push_back({ from[0], from[1] });
        points.push_back({ to[0], to[1] });
    }
       
    SDL_RenderDrawLines(&m_rendererHandle, points.data(), static_cast<int>(count));
}

