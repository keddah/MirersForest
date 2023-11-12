#pragma once
#define print(x) { std::cout<< x << std::endl; }

class GameWindow
{
public:
    static void SetRenderer(SDL_Renderer* r)
    {
        renderer = r;
    }

    static void SetWindow(SDL_Window* w)
    {
        window = w;
    }

    static SDL_Renderer* GetRenderer() { return renderer; }
    static SDL_Window* GetWindow() { return window; }

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;
};
