#include "include/videolib/renderer.hpp"

#include "videolib.hpp"

#include "include/videolib/window.hpp"
#include "include/videolib/shapes/line.hpp"
#include "src/videolib/utils/coordinate_helper.hpp"

vl::Renderer::Renderer(SDL_Renderer& rendererHandle, const Window& window)
    : m_rendererHandle { rendererHandle }
    , m_window { window }
{ }

void vl::Renderer::clear(int r, int g, int b, int a)
{
    setColor(r, g, b, a);
    SDL_RenderClear(&m_rendererHandle);
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

void vl::Renderer::setColor(int r, int g , int b, int a)
{
    SDL_SetRenderDrawColor(&m_rendererHandle, r, g, b, a);
}
