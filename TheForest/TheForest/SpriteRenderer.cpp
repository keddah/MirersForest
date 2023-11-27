#include "SpriteRenderer.h"
#include <SDL_image.h>

#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath)
{
    imagePath = spritePath;
    
}

void SpriteRenderer::Draw()
{
    SDL_Surface* image = IMG_Load(imagePath.c_str());

    if(!image)
    {
        print("Couldn't load surface.")
        return;
    }

    // It's position will be set by the owner of this object
    drawRect.w = image->w;
    drawRect.h = image->h;

    size.x = drawRect.w;
    size.y = drawRect.h;

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

    sourceRect.x = currentFrame * (size.x / frameCount);
    sourceRect.y = 0; 
    sourceRect.w = size.x * frameCount;
    sourceRect.h = size.y; 
}
