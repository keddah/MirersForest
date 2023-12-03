#pragma once
#include <iostream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Vector2.h"

class ManualRenderer
{
public:
    ManualRenderer() = default;
    ManualRenderer(const std::string& spritePath, Vector2 pos);
    ManualRenderer(const Vector2& pos, Vector2 drawSize);

    ~ManualRenderer() = default;

    // Overriden means use the position reference
    virtual void Draw(bool overridden = false);
    virtual SDL_Surface* SetSprite(const std::string& path);

    const SDL_FRect& GetRect() const { return drawRect; }
    const Vector2& GetPosition() const { return position; }
    const Vector2& GetDrawSize() const { return size; }
    
    void SetPosition(const Vector2 pos) { position = pos; }
    void SetPosition(float x, float y) { position.x = x; position.y = y; }
    void SetDrawSize(Vector2 newSize) { size = newSize; }


protected:
    std::string imagePath;
    SDL_Texture* toRender;
    Vector2 size;
    SDL_FRect drawRect = SDL_FRect();
    SDL_Rect sourceRect = SDL_Rect();

private:
    // The raw position that was assigned in the constructer
    Vector2 position;
    
};

class SpriteRenderer: public ManualRenderer
{
public:
    SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated = false);

    // Used for things that need to be renderer that don't have sprites (bullets)
    SpriteRenderer(const Vector2& pos, Vector2 drawSize);
    ~SpriteRenderer() = default;


    SpriteRenderer& operator=(const SpriteRenderer& other) {
        sourceRect = other.sourceRect;

        drawColour = other.drawColour;

        isAnimated = other.isAnimated;
        animSpeed = other.animSpeed;
        frameTimer = other.frameTimer;
        currentFrame = other.currentFrame;
        frameCount = other.frameCount;
        return *this;
    }


private:
    // Used for things that will constantly be updated (like characters)
    const Vector2& posRef;

public:
    void SetIsAnimated(bool animated = true) { isAnimated = animated; } 

    // Overriden means use the position reference
    void Draw(bool overriden = true) override;

    const Vector2& GetPositionReference() const { return posRef; }

    void SetDebugColour(SDL_Rect colour) { drawColour = colour; }

    void SetFrameCount(const short count = 1) { frameCount = count; }
    

private:
    void Animate();
    void DrawRectangle() const;
    
    // Using an Rect since it has 4 values...
    SDL_Rect drawColour = SDL_Rect{0, 125, 125, 255};

    // Animations
    short currentFrame;
    short frameCount = 4;
    float frameTimer;
    float animSpeed = .4f;
    bool isAnimated;
};
