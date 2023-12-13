#pragma once
#define print(x) { std::cout<< x << std::endl; }
#include <SDL.h>

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

    static void SetWindowSize(float w, float h)
    {
        windowWidth = w;
        windowHeight = h;
    }

    static void CloseGame()
    {
        SDL_DestroyRenderer(GetRenderer());
        SDL_DestroyWindow(GetWindow());
        SDL_Quit();
    }

    static SDL_Renderer* GetRenderer() { return renderer; }
    static SDL_Window* GetWindow() { return window; }
    
    static int GetWindowWidth() { return windowWidth; }
    static int GetWindowHeight() { return windowHeight; }

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;

    static int windowWidth;
    static int windowHeight;
};
