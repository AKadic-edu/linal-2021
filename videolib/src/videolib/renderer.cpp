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

void vl::Renderer::setColor(int r, int g , int b, int a)
{
    SDL_SetRenderDrawColor(&m_rendererHandle, r, g, b, a);
}
