#pragma once
#include <iostream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Vector2.h"

class SpriteRenderer
{
public:
    SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated = false);
    ~SpriteRenderer() = default;

    void SetIsAnimated(bool animated = true) { isAnimated = animated; } 
    
    void Draw();

    Vector2 GetDrawSize() const { return size; }


    void SetFrameCount(const short count = 1) { frameCount = count; }

private:
    std::string imagePath;
    void Animate();

    SDL_Texture* toRender;
    
    Vector2 size;
    const Vector2& position;
    
    SDL_Rect drawRect;
    SDL_Rect sourceRect;


    // Animations
    short currentFrame;
    short frameCount = 4;
    float frameTimer;
    float animSpeed = .4f;
    bool isAnimated;
};
