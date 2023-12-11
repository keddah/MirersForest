#include "Renderers.h"
#include "GameSingletons.h"

#include <SDL_image.h>


ManualRenderer::ManualRenderer(const std::string& spritePath, Vector2 pos) : position(pos)
{
    imagePath = spritePath;

    SDL_Surface* image = SetSprite(imagePath);

    if (!GameWindow::GetRenderer()) print("COuldn't get renderer.")
        thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image));

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
    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
    visible = true;
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
    sourceRect.w = size.x;
    sourceRect.h = size.y;

    visible = true;
}

// Overriden means use the position reference
void ManualRenderer::Draw(bool overriden)
{
    if(!visible)
    {
        return;
    }
    
    // Otherwise the drawRect will use the position reference that is set in the SpriteRenderer
    if (!overriden)
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
    const SDL_FPoint center {spritePivot.x, spritePivot.y};

    if(!thingsToRender[renderIndex]) print("Can't render from this index")
    
    // Responsible for drawing the texture
    SDL_RenderCopyExF(GameWindow::GetRenderer(), thingsToRender[renderIndex], &sourceRect, &drawRect, renderAngle, &center, flip? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);
}


SDL_Surface* ManualRenderer::SetSprite(const std::string& path)
{
    imagePath = path;

    SDL_Surface* image = IMG_Load(imagePath.c_str());

    if (!image)
    {
        print("Couldn't load surface.")
            return nullptr;
    }

    // Doesn't consider if the image is a spritesheet or a single image...
    // SpriteRenderer amends this.
    size.x = image->w;
    size.y = image->h;

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
}

void ManualRenderer::FromTileSheet(const SDL_Rect sourceRectangle, int tileSize)
{
    sourceRect = sourceRectangle;
    size = Vector2(tileSize, tileSize);
    drawRect.w = tileSize;
    drawRect.h = tileSize;
}
