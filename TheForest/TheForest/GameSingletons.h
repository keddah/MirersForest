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

    static void CloseGame()
    {
        SDL_DestroyRenderer(GetRenderer());
        SDL_DestroyWindow(GetWindow());
        SDL_Quit();
    }

    static SDL_Renderer* GetRenderer() { return renderer; }
    static SDL_Window* GetWindow() { return window; }
    
    static Vector2 GetWindowSize()
    {
        int w;
        int h;
        SDL_GetWindowSize(GetWindow(), &w, &h);
        return Vector2(w, h);
    }

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    
    static Vector2 windowSize;
};
