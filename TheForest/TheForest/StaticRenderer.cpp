#include "SpriteRenderer.h"
#include "GameSingletons.h"

#include <SDL_image.h>


StaticRenderer::StaticRenderer(const std::string& spritePath, Vector2 pos) : position(pos)
{
    imagePath = spritePath;

    SDL_Surface* image = SetSprite(imagePath);

    if (!GameWindow::GetRenderer()) print("COuldn't get renderer.")
        toRender = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);

    if (!toRender)
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
}

// Overriden means use the position reference
void StaticRenderer::Draw(bool overriden)
{
    if (!overriden)
    {
        drawRect.x = position.x;
        drawRect.y = position.y;
    }

    //print("source: " << sourceRect.x << ", " << sourceRect.y << ", " << sourceRect.w << ", " << sourceRect.h)
    //print("dest: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)

    // Responsible for drawing the texture 
    SDL_RenderCopyF(GameWindow::GetRenderer(), toRender, &sourceRect, &drawRect);
}


SDL_Surface* StaticRenderer::SetSprite(const std::string& path)
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