/**************************************************************************************************************
* Manual Renderer - Code
*
* The code file for the Manual renderer class. Responsible for drawing things to the screen by loading SDL surfaces and creating textures
* from them. Depending on which constructor is used, several textures can be created for each instance of this class.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Renderers.h"

#include <SDL_image.h>


ManualRenderer::ManualRenderer(const std::string& spritePath, Vector2 pos) : position(pos)
{
    SDL_Surface* image = ManualRenderer::SetSprite(spritePath);

    if (!renderer)
    {
        print("COuldn't get renderer.")
        return;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, image);
    thingsToRender.emplace_back(tex);
    SDL_FreeSurface(image);

    if (!thingsToRender[renderIndex])
    {
        print("nothing to render.")
        return;
    }

    // The size is set in the SetSprite function
    drawRect.x = position.x;
    drawRect.y = position.y;
    drawRect.w = size.x;
    drawRect.h = size.y;

    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);
}

ManualRenderer::ManualRenderer(const Vector2& pos, Vector2 drawSize)
{
    position = pos;
    size = drawSize;

    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);
}

// Overriden means use the position reference
void ManualRenderer::Draw(bool referenced)
{
    if(!visible) return;

    // Otherwise the drawRect will use the position reference that is set in the SpriteRenderer
    if (!referenced)
    {
        drawRect.x = position.x;
        drawRect.y = position.y;
    }
    drawRect.w = size.x;
    drawRect.h = size.y;

    
    //print("source: " << sourceRect.x << ", " << sourceRect.y << ", " << sourceRect.w << ", " << sourceRect.h)
    //print("dest: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)
    // print("renderer: " << drawRect.x << ", " << drawRect.y)

    if(!customPivot) spritePivot = { drawRect.w/2,drawRect.h/2};
    const SDL_FPoint pivot {spritePivot.x, spritePivot.y};

    // If there aren't any textures to draw... draw a rectangle instead
    if(thingsToRender.empty())
    {
        DrawRectangle();
        return;
    }
    
    if(!thingsToRender[renderIndex]) print("Can't render from this index")
    
    // Responsible for drawing the texture
    SDL_RenderCopyExF(renderer, thingsToRender[renderIndex], &sourceRect, &drawRect, renderAngle, &pivot, flip? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);
}

void ManualRenderer::DrawRectangle() const
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    SDL_RenderFillRectF(renderer, &drawRect);
}

SDL_Surface* ManualRenderer::SetSprite(const std::string& path)
{
    imagePath = path;

    SDL_Surface* image = IMG_Load(imagePath.c_str());

    if (!image)
    {
        print("Couldn't load surface. Bad file path")
        return nullptr;
    }

    // Doesn't consider if the image is a spritesheet or a single image...
    // SpriteRenderer amends this.
    size.x = static_cast<float>(image->w);
    size.y = static_cast<float>(image->h);

    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    return image;
}

void ManualRenderer::SetDrawSize(const Vector2 newSize)
{
    size = newSize;
    drawRect.w = size.x;
    drawRect.h = size.y;
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);
}

void ManualRenderer::SetDrawSize(float w, float h)
{
    size = {w, h};
    drawRect.w = size.x;
    drawRect.h = size.y;
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);
}

void ManualRenderer::FromTileSheet(const SDL_Rect sourceRectangle, int tileSize)
{
    sourceRect = sourceRectangle;
    size = Vector2(static_cast<float>(tileSize), static_cast<float>(tileSize));
    drawRect.w = static_cast<float>(tileSize);
    drawRect.h = static_cast<float>(tileSize);
}
