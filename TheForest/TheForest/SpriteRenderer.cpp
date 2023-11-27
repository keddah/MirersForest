#include "SpriteRenderer.h"
#include <SDL_image.h>

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated): position(pos)
{
    imagePath = spritePath;
    isAnimated = animated;
}

void SpriteRenderer::Draw()
{
    SDL_Surface* image = ResetSprite(imagePath);

    if(!GameWindow::GetRenderer()) print("COuldn't get renderer.")
    toRender = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);
    
    if(!toRender)
    {
        print("nothing to render.")
        return;
    }
    // Goes to the next frame 
    Animate();
    
    if(!isAnimated)
    {
        size.x = image->w;
        size.y = image->h;
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = size.x * 2;
        sourceRect.h = size.y * 2;
    }
    
    drawRect.x = position.x;
    drawRect.y = position.y;
    
    print("source: " << sourceRect.x << ", " << sourceRect.y << ", " << sourceRect.w << ", " << sourceRect.h)
    print("dest: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)
    
    // Responsible for drawing the texture 
    SDL_RenderCopy(GameWindow::GetRenderer(), toRender, &sourceRect, &drawRect);

    SDL_FreeSurface(image);
}

SDL_Surface* SpriteRenderer::ResetSprite(const std::string& path)
{
    imagePath = path;
    
    SDL_Surface* image = IMG_Load(imagePath.c_str());

    if(!image)
    {
        print("Couldn't load surface.")
        return nullptr;
    }

    if(isAnimated)
    {
        size.x = image->w / frameCount;
        size.y = image->h;
    }

    else
    {
        size.x = image->w;
        size.y = image->h;
    }
    
    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    return image;
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
