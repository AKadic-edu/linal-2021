#include <SDL.h>

struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Graph {

};

void sleep(int ms)
{
    SDL_Delay(ms);
}

void draw_line(SDL_Renderer& r, Line l)
{
    SDL_RenderDrawLine(&r, l.x1, l.y1, l.x2, l.y2);
}

void draw_graph(const Graph& const graph)
{
    int window_width = 640;
    int window_height = 480;

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Jeu de la vie", 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear window
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    Line h { 0, window_height / 2, window_width, window_height / 2 };
    Line v { window_width / 2, 0, window_width / 2, window_height };

    draw_line(*renderer, h);
    draw_line(*renderer, v);

    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Wait for 5 sec
    sleep(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
	Graph g;

	draw_graph(g);

	return 0;
}