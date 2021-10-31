#include "week1.hpp"

#include <mathlib/Vector.hpp>

bool g_running = true;

int g_windowWidth = 640;
int g_windowHeight = 480;
ml::Vector<int, 2> g_windowCenter { g_windowWidth / 2, g_windowHeight / 2 };

struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
};

void drawLine(SDL_Renderer& r, Line l)
{
    int y1 = g_windowHeight - l.y1;
    int y2 = g_windowHeight - l.y2;

    SDL_RenderDrawLine(&r, l.x1, y1, l.x2, y2);
}

struct Graph {
    int xSize;
    int ySize;
};

class GraphRenderer {
public:
    GraphRenderer(const Graph& g)
        : m_g { g }
    { }

    void draw(SDL_Renderer& r)
    {
        int grey { 200 };
        SDL_SetRenderDrawColor(&r, grey, grey, grey, grey);
        drawGrid(r);

        SDL_SetRenderDrawColor(&r, 0, 0, 0, 0);
        drawAxes(r);
    }

    void drawVector(SDL_Renderer& r, ml::Vector<int, 2> v)
    {
        int x { g_windowWidth * v[0] / m_g.xSize };
        int y { g_windowHeight * v[1] / m_g.ySize };
        Line l { g_windowCenter[0], g_windowCenter[1], g_windowCenter[0] + x, g_windowCenter[1] + y };

        drawLine(r, l);
    }
private:
    const Graph& m_g;

    void drawAxes(SDL_Renderer& r)
    {
        Line hAxis { 0, g_windowCenter[1], g_windowWidth, g_windowCenter[1] };
        Line vAxis { g_windowCenter[0], 0, g_windowCenter[0], g_windowHeight };

        drawLine(r, hAxis);
        drawLine(r, vAxis);
    }

    void drawGrid(SDL_Renderer& r)
    {
        float xSlope { static_cast<float>(g_windowWidth) / m_g.xSize };
        float ySlope { static_cast<float>(g_windowHeight) / m_g.ySize };

        for (int i { 1 }; i < m_g.xSize; ++i) {
            int offset { static_cast<int>(i * xSlope) };

            Line l { offset, 0, offset, g_windowHeight };

            drawLine(r, l);
        }

        for (int i { 0 }; i < m_g.ySize; ++i) {
            int offset { static_cast<int>(i * ySlope) };

            Line l { 0, offset, g_windowWidth, offset };

            drawLine(r, l);
        }
    }
};

void sleep(int ms)
{
    SDL_Delay(ms);
}

void poll_input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
        case SDL_WINDOWEVENT:
        {
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                g_running = false;
                break;
            case SDL_WINDOWEVENT_RESIZED:
            {
                int newWidth = e.window.data1;
                int newHeight = e.window.data2;

                g_windowWidth = newWidth;
                g_windowHeight = newHeight;
                g_windowCenter = { newWidth / 2, newHeight / 2 };
            }
            default:
                break;
            }
        }
        default:
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    Graph g { 10, 10 };
    GraphRenderer graphRenderer { g };

    ml::Vector<int, 2> a { 2, 5 };
    ml::Vector<int, 2> b { -1, -2 };
    ml::Vector<int, 2> abAdded { a + b };
    ml::Vector<int, 2> abSubtracted { a - b };

    SDL_Window* window = SDL_CreateWindow
    (
        "Jeu de la vie",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        g_windowWidth,
        g_windowHeight,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (g_running) {
        poll_input();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        graphRenderer.draw(*renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        graphRenderer.drawVector(*renderer, a);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        graphRenderer.drawVector(*renderer, b);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        graphRenderer.drawVector(*renderer, abAdded);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        graphRenderer.drawVector(*renderer, abSubtracted);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
