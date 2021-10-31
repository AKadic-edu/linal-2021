#include "include/videolib/instance.hpp"

#include "videolib.hpp"

#include "include/videolib/key.hpp"
#include "include/videolib/renderer.hpp"
#include "include/videolib/window.hpp"

vl::Instance::~Instance() = default;

vl::Instance::Instance(Window& window)
    : m_window { window }
    , m_rendererHandle { nullptr }
    , m_windowHandle { nullptr }
    , m_running { true }
{ }

int vl::Instance::run(std::function<void(Renderer&)> cb)
{
	setup();

    while (m_running) {
        pollInput();
        cb(*m_renderer);
        render();
    }

	teardown();

	return 0;
}

void vl::Instance::onKeyDown(KeyHandler h)
{
    m_keyHandlers.push_back(h);
}

void vl::Instance::onMouseMove(MouseHandler h)
{
    m_mouseHandlers.push_back(h);
}

void vl::Instance::setup()
{
    m_windowHandle = SDL_CreateWindow
    (
        "Week 2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_window.width,
        m_window.height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    m_rendererHandle = SDL_CreateRenderer(m_windowHandle, -1, SDL_RENDERER_ACCELERATED);
    m_renderer = std::make_unique<Renderer>(*m_rendererHandle, m_window);
}

void vl::Instance::pollInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            handleKeyDown(e.key);
            break;
        case SDL_MOUSEMOTION:
            handleMouseMove(e.motion);
            break;
        case SDL_WINDOWEVENT:
        {
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                m_running = false;
                break;
            case SDL_WINDOWEVENT_RESIZED:
            {
                int newWidth = e.window.data1;
                int newHeight = e.window.data2;

                m_window.width = newWidth;
                m_window.height = newHeight;
                break;
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
}

void vl::Instance::render()
{
    SDL_RenderPresent(m_rendererHandle);
}

void vl::Instance::teardown()
{
	SDL_DestroyRenderer(m_rendererHandle);
	SDL_DestroyWindow(m_windowHandle);
	SDL_Quit();
}

void vl::Instance::handleKeyDown(const SDL_KeyboardEvent& e)
{
    for (auto& h : m_keyHandlers) {
        h(convertKey(e.keysym.sym));
    }
}

void vl::Instance::handleMouseMove(const SDL_MouseMotionEvent& e)
{
    float normalizedX { -1.0f + 2.0f * (static_cast<float>(e.x) / m_window.width) };
    float normalizedY { 1.0f - 2.0f * (static_cast<float>(e.y) / m_window.height) };

    for (auto& h: m_mouseHandlers) {
        h(normalizedX, normalizedY);
    }
}

vl::Key vl::Instance::convertKey(SDL_Keycode key) const
{
    if (key == SDLK_k) return vl::Key::k;
    if (key == SDLK_l) return vl::Key::l;

    throw std::exception { "Key not mapped"};
}
