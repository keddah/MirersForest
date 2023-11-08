#pragma once

class GameRenderer
{
public:
    static void SetRenderer(SDL_Renderer* r)
    {
        renderer = r;
    }


    static SDL_Renderer* GetRenderer() { return renderer; }

private:
    static SDL_Renderer* renderer;
};
