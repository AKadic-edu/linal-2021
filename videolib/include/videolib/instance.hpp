#pragma once

#ifndef VIDEOLIB_INSTANCE_HPP
#define VIDEOLIB_INSTANCE_HPP

#include <functional>
#include <memory>

struct SDL_Renderer;
struct SDL_Window;

namespace vl {
    class Renderer;
    struct Window;

    class Instance {
    public:
        Instance(Window&);
        Instance(Instance const&) = delete;
        Instance(Instance&&) = delete;
        Instance& operator=(Instance const&) = delete;
        Instance& operator=(Instance&&) = delete;
        virtual ~Instance();

        int run(std::function<void(Renderer&)>);
    private:
        bool m_running;

        std::unique_ptr<Renderer> m_renderer;
        Window& m_window;

        SDL_Renderer* m_rendererHandle;
        SDL_Window* m_windowHandle;

        void pollInput();
        void render();
        void setup();
        void teardown();
    };
}

#endif // !VIDEOLIB_INSTANCE_HPP
