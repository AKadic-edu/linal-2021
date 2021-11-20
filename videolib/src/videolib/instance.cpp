#include "include/videolib/instance.hpp"

#include "videolib.hpp"

#include "include/videolib/key.hpp"
#include "include/videolib/renderer.hpp"
#include "include/videolib/window.hpp"
#include "src/videolib/utils/coordinate_helper.hpp"

vl::Instance::~Instance() = default;

vl::Instance::Instance(Window& window)
    : m_window { window }
    , m_rendererHandle { nullptr }
    , m_windowHandle { nullptr }
    , m_running { true }
    , m_mouseHold { false }
    , m_mouse { 0.0f, 0.0f }
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

void vl::Instance::onMouseDown(MouseHandler h)
{
    m_mouseDownHandlers.push_back(h);
}

void vl::Instance::onMouseHold(MouseHandler h)
{
    m_mouseHoldHandlers.push_back(h);
}

void vl::Instance::onMouseMove(MouseHandler h)
{
    m_mouseMoveHandlers.push_back(h);
}

void vl::Instance::onMouseScroll(MouseHandler h)
{
    m_mouseScrollHandlers.push_back(h);
}

void vl::Instance::onMouseUp(MouseHandler h)
{
    m_mouseUpHandlers.push_back(h);
}

void vl::Instance::setup()
{
    m_windowHandle = SDL_CreateWindow
    (
        m_window.title.c_str(),
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
        case SDL_MOUSEBUTTONDOWN:
            handleMouseDown(e.button);
            break;
        case SDL_MOUSEMOTION:
            handleMouseMove(e.motion);
            break;
        case SDL_MOUSEWHEEL:
            handleMouseScroll(e.wheel);
            break;
        case SDL_MOUSEBUTTONUP:
            handleMouseUp(e.button);
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

    if (m_mouseHold) {
        handleMouseHold(m_mouse[0], m_mouse[1]);
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

void vl::Instance::handleMouseDown(const SDL_MouseButtonEvent& e)
{
    m_mouseHold = true;

    auto relative = CoordinateHelper::toRelative(viewport(), { e.x, e.y });

    for (auto& h : m_mouseDownHandlers) {
        h(relative[0], relative[1]);
    }
}

void vl::Instance::handleMouseHold(float x, float y)
{
    for (auto& h : m_mouseHoldHandlers) {
        h(x, y);
    }
}

void vl::Instance::handleMouseMove(const SDL_MouseMotionEvent& e)
{
    auto relative = CoordinateHelper::toRelative(viewport(), { e.x, e.y });

    m_mouse = relative;

    for (auto& h: m_mouseMoveHandlers) {
        h(relative[0], relative[1]);
    }
}

void vl::Instance::handleMouseScroll(const SDL_MouseWheelEvent& e)
{
    auto x = static_cast<float>(e.x);
    auto y = static_cast<float>(e.y);

    for (auto& h : m_mouseScrollHandlers) {
        h(x, y);
    }
}

void vl::Instance::handleMouseUp(const SDL_MouseButtonEvent& e)
{
    m_mouseHold = false;

    auto relative = CoordinateHelper::toRelative(viewport(), { e.x, e.y });

    for (auto& h : m_mouseUpHandlers) {
        h(relative[0], relative[1]);
    }
}

ml::Vector<float, 2> vl::Instance::mouse() const
{
    return m_mouse;
}

vl::Key vl::Instance::convertKey(SDL_Keycode key) const
{
    if (key == SDLK_a) return vl::Key::a;
    if (key == SDLK_b) return vl::Key::b;
    if (key == SDLK_c) return vl::Key::c;
    if (key == SDLK_d) return vl::Key::d;
    if (key == SDLK_e) return vl::Key::e;
    if (key == SDLK_f) return vl::Key::f;
    if (key == SDLK_g) return vl::Key::g;
    if (key == SDLK_h) return vl::Key::h;
    if (key == SDLK_i) return vl::Key::i;
    if (key == SDLK_j) return vl::Key::j;
    if (key == SDLK_k) return vl::Key::k;
    if (key == SDLK_l) return vl::Key::l;
    if (key == SDLK_m) return vl::Key::m;
    if (key == SDLK_n) return vl::Key::n;
    if (key == SDLK_o) return vl::Key::o;
    if (key == SDLK_p) return vl::Key::p;
    if (key == SDLK_q) return vl::Key::q;
    if (key == SDLK_r) return vl::Key::r;
    if (key == SDLK_s) return vl::Key::s;
    if (key == SDLK_t) return vl::Key::t;
    if (key == SDLK_u) return vl::Key::u;
    if (key == SDLK_v) return vl::Key::v;
    if (key == SDLK_w) return vl::Key::w;
    if (key == SDLK_x) return vl::Key::x;
    if (key == SDLK_y) return vl::Key::y;
    if (key == SDLK_z) return vl::Key::z;

    if (key == SDLK_DOWN) return vl::Key::down;
    if (key == SDLK_LEFT) return vl::Key::left;
    if (key == SDLK_RIGHT) return vl::Key::right;
    if (key == SDLK_UP) return vl::Key::up;
    if (key == SDLK_LSHIFT) return vl::Key::shift;

    throw std::exception { "Key not mapped"};
}

ml::Vector<int, 2> vl::Instance::viewport() const
{
    return { m_window.width, m_window.height };
}
