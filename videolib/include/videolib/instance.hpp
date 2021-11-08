#pragma once

#ifndef VIDEOLIB_INSTANCE_HPP
#define VIDEOLIB_INSTANCE_HPP

#include <functional>
#include <memory>
#include <vector>

#include <mathlib/vector.hpp>

#include "key.hpp"

struct SDL_KeyboardEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseWheelEvent;
struct SDL_Renderer;
struct SDL_Window;

namespace vl {
    class Renderer;
    struct Window;

    class Instance {
    public:
        typedef std::function<void(const Key&)> KeyHandler;
        typedef std::function<void(float, float)> MouseHandler;

        Instance(Window&);
        Instance(Instance const&) = delete;
        Instance(Instance&&) = delete;
        Instance& operator=(Instance const&) = delete;
        Instance& operator=(Instance&&) = delete;
        virtual ~Instance();

        int run(std::function<void(Renderer&)>);

        void onKeyDown(KeyHandler);
        void onMouseDown(MouseHandler);
        void onMouseHold(MouseHandler);
        void onMouseMove(MouseHandler);
        void onMouseScroll(MouseHandler);
        void onMouseUp(MouseHandler);

        ml::Vector<float, 2> mouse() const;
    private:
        bool m_running;

        std::unique_ptr<Renderer> m_renderer;
        Window& m_window;

        SDL_Renderer* m_rendererHandle;
        SDL_Window* m_windowHandle;

        std::vector<KeyHandler> m_keyHandlers;
        std::vector<MouseHandler>
            m_mouseDownHandlers,
            m_mouseHoldHandlers,
            m_mouseMoveHandlers,
            m_mouseScrollHandlers,
            m_mouseUpHandlers;
        bool m_mouseHold;
        ml::Vector<float, 2> m_mouse;

        void pollInput();
        void render();
        void setup();
        void teardown();

        void handleKeyDown(const SDL_KeyboardEvent&);
        void handleMouseDown(const SDL_MouseButtonEvent&);
        void handleMouseHold(float x, float y);
        void handleMouseMove(const SDL_MouseMotionEvent&);
        void handleMouseScroll(const SDL_MouseWheelEvent&);
        void handleMouseUp(const SDL_MouseButtonEvent&);

        vl::Key convertKey(signed int) const;
        ml::Vector<int, 2> viewport() const;
    };
}

#endif // !VIDEOLIB_INSTANCE_HPP
