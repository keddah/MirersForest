#pragma once
#include <iostream>
#include <random>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

#include "Vector2.h"

class ManualRenderer
{
public:
    ManualRenderer() = default;
    ManualRenderer(const std::string& spritePath, Vector2 pos);
    ManualRenderer(const Vector2& pos, Vector2 drawSize);

    // Delete all the textures then empty the vector.
    virtual ~ManualRenderer() = default;
        // for(const auto& thing: thingsToRender) delete &thing;

    // Overriden means use the position reference
    virtual void Draw(short currentSlide, bool overridden = false);

    const SDL_FRect& GetRect() const { return drawRect; }
    const Vector2& GetPosition() const { return position; }
    float GetRenderAngle() const { return renderAngle; }
    const Vector2& GetDrawSize() const { return size; }
    const Vector2& GetSpriteCenter() const { return spritePivot; }

    virtual void SetVisibility(bool isVisible) { visible = isVisible; }
    virtual void SetLevelSlide(short slide) { levelSlide = slide; }
    virtual short GetLevelSlide() const { return levelSlide; }
    
    virtual void SetDrawSize(Vector2 newSize);
    void SetPosition(const Vector2 pos) { position = pos; }
    void SetPosition(const float x, const float y) { position = {x, y}; }
    virtual void SetFlip(const bool shouldFlip) { flip = shouldFlip; }
    void SetRenderAngle(const float angle) { renderAngle = angle; }
    void SetSpritePivot(const float x, const float y)
    {
        spritePivot = { x, y };
        customPivot = true;
    }
    void SetSpritePivot(const Vector2 pivot)
    {
        spritePivot = pivot;
        customPivot = true;
    }

    
    virtual void ChangeSpriteSheet(short index) { renderIndex = index; }
    
    void FromTileSheet(SDL_Rect sourceRectangle, int tileSize);    

protected:
    virtual SDL_Surface* SetSprite(const std::string& path);

    bool visible = true;
    short levelSlide;
    
    std::string imagePath;
    std::vector<SDL_Texture*> thingsToRender = std::vector<SDL_Texture*>();
    short renderIndex = 0;
    Vector2 size;
    SDL_FRect drawRect = SDL_FRect();
    SDL_Rect sourceRect = SDL_Rect();
    float renderAngle;
    Vector2 spritePivot;

    bool flip;
    
private:
    // The raw position that was assigned in the constructor
    Vector2 position;
    bool customPivot;
};

class SpriteRenderer: public ManualRenderer
{
public:
    SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated = false);
    SpriteRenderer(const std::vector<std::string>& spritePaths, const Vector2& pos, bool animated = true);

    // Used for things that need to be renderer that don't have sprites (bullets)
    SpriteRenderer(const Vector2& pos, Vector2 drawSize);

private:
    // Used for things that will constantly be updated (like characters)
    const Vector2& posRef;

public:
    void SetIsAnimated(bool animated = true) { isAnimated = animated; } 
    
    // Overriden means use the position reference
    void Draw(short currentSlide = 0, bool overriden = true) override;

    const Vector2& GetPositionReference() const { return posRef; }

    void SetRenderColour(SDL_Colour colour) { drawColour = colour; }

    void SetFrameCount(const short count = 1) { frameCount = count; }
    void SetAnimSpeed(const float speed) { animSpeed = speed; }
    

private:
    void Animate();
    void DrawRectangle() const;

    // Using an Rect since it has 4 values...
    SDL_Colour drawColour = {0, 125, 125, 255};

    // Animations
    short currentFrame;
    short frameCount = 4;
    float frameTimer;
    float animSpeed = .35f;
    bool isAnimated;
};
