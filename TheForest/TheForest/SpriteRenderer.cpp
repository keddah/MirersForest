#include "SpriteRenderer.h"
#include <SDL_image.h>

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, bool animated)
{
    imagePath = spritePath;
    isAnimated = animated;
}

void SpriteRenderer::Draw()
{
    SDL_Surface* image = IMG_Load(imagePath.c_str());

    if(!image)
    {
        print("Couldn't load surface.")
        return;
    }

    if(isAnimated)
    {
        size.x = image->w / frameCount;
        size.y = image->h;
    }

    else
    {
        size.x = drawRect.w;
        size.y = drawRect.h;
    }
    
    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    if(!GameWindow::GetRenderer()) print("COuldn't get renderer.")
    toRender = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);
    
    if(!toRender)
    {
        print("nothing to render.")
        return;
    }
    // Goes to the next frame 
    Animate();
    
    // Responsible for drawing the texture 
    SDL_RenderCopy(GameWindow::GetRenderer(), toRender, &sourceRect, &drawRect);

    SDL_FreeSurface(image);
}

void SpriteRenderer::Animate()
{
    if(!isAnimated) return;

    sourceRect.x = size.x * currentFrame;
    sourceRect.y = 0; 
    sourceRect.w = size.x;
    sourceRect.h = size.y;

    frameTimer += Time::GetDeltaTime() * 50;
    if (frameTimer > animSpeed)
    {
        currentFrame++;
        frameTimer = 0;
    }

    if (currentFrame > frameCount - 1) currentFrame = 0;
}
