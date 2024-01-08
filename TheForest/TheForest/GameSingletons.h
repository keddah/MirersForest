/**************************************************************************************************************
* Game Singletons - Header
*
* The header file for the Game window class (static). This is used so that the SDL renderer and window can be accessed without
* a reference to other things. The renderer and window need to be set when SDL is initiated. For the level slides, this was needed
* to get the window width (progressing relies on the screen width).
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#define print(x) { std::cout<< x << std::endl; }
#include <SDL.h>

class GameWindow
{
public:
    static void SetRenderer(SDL_Renderer* r)
    {
        if(r) renderer = r;
    }

    static void SetWindow(SDL_Window* w)
    {
        if(w) window = w;
    }

    static void SetWindowSize(int w, int h)
    {
        windowWidth = w;
        windowHeight = h;
    }

    static void CloseGame()
    {
        if (renderer)
        {
            SDL_DestroyRenderer(GetRenderer());
            renderer = nullptr;
        }

        if (window)
        {
            SDL_DestroyWindow(GetWindow());
            window = nullptr;
        }

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
