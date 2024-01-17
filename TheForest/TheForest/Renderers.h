/**************************************************************************************************************
* Renderers - Header
*
* The header file for the Manual Renderer, Sprite Renderer and Text Renderer classes. The manual Renderer is the parent class which the Sprite and Text renderers
* are derived from. All classes have a Draw function.
* Since the manual renderers aren't using a reference for its position, it means it isn't used for a character or something that constantly moves (it shouldn't be).
* Sprite renderers are used for things that constantly move or anything that needs to be animated.
* The Sprite and Manual renderers can also load multiple textures at once and change between them if necessary.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include <iostream>

#include <SDL_render.h>

#include "SDL_ttf.h"
#include <vector>

#include "GameSingletons.h"
#include "Vector2.h"

// Manual meaning the position is set manually (without using a reference)
class ManualRenderer
{
public:
    ManualRenderer() = default;
    ManualRenderer(SDL_Texture* texture, Vector2 pos, SDL_Rect source);
    ManualRenderer(const std::string& spritePath, Vector2 pos);
    ManualRenderer(const Vector2& pos, Vector2 drawSize);

    virtual ~ManualRenderer() { thingsToRender.clear(); }

    // Delete all the textures then empty the vector.
    virtual void DestroyAllTextures()
    {
        for(const auto& tex: thingsToRender) { SDL_DestroyTexture(tex); }
        thingsToRender.clear();
    }

    // Overriden means use the position reference
    virtual void Draw(bool referenced = false);

    virtual const SDL_FRect& GetRect() const { return drawRect; }
    virtual const Vector2& GetPosition() const { return position; }
    float GetRenderAngle() const { return renderAngle; }
    virtual const Vector2& GetDrawSize() const { return size; }
    virtual const Vector2& GetSpriteCenter() const { return spritePivot; }

    virtual void SetVisibility(bool isVisible) { visible = isVisible; }
    virtual bool IsVisible() const { return visible; }

    virtual void SetRenderColour(SDL_Colour colour) { drawColour = colour; }

    virtual void SetDrawSize(Vector2 newSize);
    virtual void SetDrawSize(float w, float h);
    virtual void SetPosition(const Vector2 pos) { position = pos; }
    virtual void SetPosition(const float x, const float y) { position = {x, y}; }
    virtual void SetFlip(const bool shouldFlip) { flip = shouldFlip; }
    virtual void SetRenderAngle(const float angle) { renderAngle = angle; }
    virtual void SetSpritePivot(const Vector2 pivot)
    {
        spritePivot = pivot;
        customPivot = true;
    }

    virtual void ChangeSpriteSheet(short index) { renderIndex = index; }
    
    void FromTileSheet(SDL_Rect sourceRectangle, int tileSize = 16);    

    SDL_Texture* GetTexture() { return thingsToRender[0]; }

protected:
    virtual SDL_Surface* SetSprite(const std::string& path);

    virtual void DrawRectangle() const;
    
    bool visible = true;
    
    std::string imagePath;
    std::vector<SDL_Texture*> thingsToRender = std::vector<SDL_Texture*>();
    short renderIndex = 0;
    Vector2 size;
    SDL_FRect drawRect = SDL_FRect();
    SDL_Rect sourceRect = SDL_Rect();
    float renderAngle = 0;
    Vector2 spritePivot;

    // The raw position that was assigned in the constructor
    Vector2 position;

    SDL_Colour drawColour = {0, 125, 125, 255};

    bool flip = false;

    SDL_Renderer* renderer = GameWindow::GetRenderer(); 
    
private:
    bool customPivot = false;
};




class SpriteRenderer: public ManualRenderer
{
public:
    SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated = false, bool isLooping = true);
    SpriteRenderer(const std::vector<std::string>& spritePaths, const Vector2& pos, bool animated = true, bool isLooping = true);

private:
    // Used for things that will constantly be updated (like characters)
    const Vector2& posRef;

public:
    void SetIsAnimated(bool animated = true) { isAnimated = animated; } 
    bool IsAnimating() const { return isAnimated; }
    short GetCurrentFrame() const { return currentFrame; }
    void SetCurrentFrame(const short frame) { currentFrame = frame; }

    void ChangeSpriteSheet(short index) override
    {
        renderIndex = index;

        // Changing the size of one frame
        Resize();
    }

    
    // Overriden means use the position reference
    void Draw(bool referenced = true) override;
    
    // Plays a one time animation (doesn't loop around after all the frames have been played)
    void PlayAnimation(bool referenced = true);
    
    const Vector2& GetPositionReference() const { return posRef; }

    short GetFrameCount() const { return frameCount; }
    void SetFrameCount(const short count = 1)
    {
        frameCount = count;

        // Changing the size of one frame
        Resize();
    }

    float GetAnimSpeed() const { return animSpeed; }
    void SetAnimSpeed(const float speed) { animSpeed = speed; }
    

private:
    void Resize()
    {
        int width, height;
        SDL_QueryTexture(thingsToRender[renderIndex],0,0, &width, &height);

        size.x = width / frameCount; 
        size.y = height;

        drawRect.w = size.x;
        drawRect.h = size.y;
        sourceRect.w = static_cast<int>(size.x);
        sourceRect.h = static_cast<int>(size.y);
    }
    
    // Animations
    void Animate();
    short currentFrame;
    short frameCount = 1;
    float frameTimer;
    float animSpeed = .35f;
    bool isAnimated;
    bool looping;
};




class TextRenderer : public ManualRenderer
{
public:
    TextRenderer(const std::string& filePath, std::string displayText, short _fontSize, Vector2 pos);
    ~TextRenderer() override
    {
        for(const auto& texture : thingsToRender) SDL_DestroyTexture(texture);
        ManualRenderer::~ManualRenderer();
        TTF_Quit();
    }

    void SetText(const std::string& displayText);
    void SetFontSize(const short newSize) { fontSize = newSize; }

private:
    std::string text;
    short fontSize;
};