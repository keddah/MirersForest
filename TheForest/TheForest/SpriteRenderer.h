#pragma once
#include <iostream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Vector2.h"

class StaticRenderer
{
public:
    StaticRenderer() = default;
    StaticRenderer(const std::string& spritePath, Vector2 pos);
    ~StaticRenderer() = default;

    virtual void Draw(bool overridden = false);
    virtual SDL_Surface* SetSprite(const std::string& path);

    const Vector2& GetPosition() const { return position; }
    const Vector2& GetDrawSize() const { return size; }


protected:
    std::string imagePath;
    SDL_Texture* toRender;
    Vector2 size;
    SDL_Rect drawRect = SDL_Rect();
    SDL_Rect sourceRect = SDL_Rect();

private:
    // The raw position that was assigned in the constructer
    Vector2 position;
    
};

class SpriteRenderer: public StaticRenderer
{
public:
    SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated = false);
    ~SpriteRenderer() = default;

    void SetIsAnimated(bool animated = true) { isAnimated = animated; } 
    
    void Draw(bool overriden) override;

    const Vector2& GetPositionReference() const { return posRef; }


    void SetFrameCount(const short count = 1) { frameCount = count; }


private:
    void Animate();

    // Used for things that will constantly be updated (like characters)
    const Vector2& posRef;
    
    // Animations
    short currentFrame;
    short frameCount = 4;
    float frameTimer;
    float animSpeed = .4f;
    bool isAnimated;
};
