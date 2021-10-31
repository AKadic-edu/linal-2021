#pragma once

#ifndef VIDEOLIB_INSTANCE_HPP
#define VIDEOLIB_INSTANCE_HPP

#include <functional>
#include <memory>
#include <vector>

#include "key.hpp"

struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
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
        void onMouseMove(MouseHandler);
    private:
        bool m_running;

        std::unique_ptr<Renderer> m_renderer;
        Window& m_window;

        SDL_Renderer* m_rendererHandle;
        SDL_Window* m_windowHandle;

        std::vector<KeyHandler> m_keyHandlers;
        std::vector<MouseHandler> m_mouseHandlers;

        void pollInput();
        void render();
        void setup();
        void teardown();

        void handleKeyDown(const SDL_KeyboardEvent&);
        void handleMouseMove(const SDL_MouseMotionEvent&);

        vl::Key convertKey(signed int) const;
    };
}

#endif // !VIDEOLIB_INSTANCE_HPP
