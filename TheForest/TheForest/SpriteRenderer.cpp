/**************************************************************************************************************
* Sprite Renderer - Code
*
* The code file for the Sprite renderer class. Responsible for drawing things to the screen by loading SDL surfaces and creating textures
* from them. Depending on which constructor is used, several textures can be created for each instance of this class. The draw function is
* inherited from the Manual renderer but is overriden to allow for animations
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Renderers.h"

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated, bool isLooping): posRef(pos)
{
    imagePath = spritePath;
    isAnimated = animated;

    if (!renderer)
    {
        print("COuldn't get renderer.")
        return;
    }

    SDL_Surface* image = ManualRenderer::SetSprite(imagePath);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, image);
    thingsToRender.emplace_back(tex);
    
    if (!thingsToRender[renderIndex])
    {
        print("nothing to render.")
        return;
    }

    size.x = isAnimated? static_cast<float>(image->w / frameCount): static_cast<float>(image->w);
    size.y = static_cast<float>(image->h);

    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);

    SDL_FreeSurface(image);

    looping = isLooping;
    
    // Start on a random frame so that the animations aren't synced up
    if(isAnimated && !isLooping) currentFrame = std::rand() % ( frameCount + 1 );
}

// This constructor is used for animated things
SpriteRenderer::SpriteRenderer(const std::vector<std::string>& spritePaths, const Vector2& pos, bool animated, bool isLooping): posRef(pos)
{
    imagePath = spritePaths[0];
    isAnimated = animated;

    if (!renderer)
    {
        print("COuldn't get renderer.")
        return;
    }

    for (const auto& path : spritePaths)
    {
        SDL_Surface* image = ManualRenderer::SetSprite(path);
        
        
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, image);
        thingsToRender.emplace_back(tex);

        size.x = isAnimated? static_cast<float>(image->w / frameCount): static_cast<float>(image->w);
        size.y = static_cast<float>(image->h);
        SDL_FreeSurface(image);

        // It's position will be set by the owner of this object
        drawRect.w = size.x;
        drawRect.h = size.y;

        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = static_cast<int>(size.x);
        sourceRect.h = static_cast<int>(size.y);


        // Start on a random frame so that the animations aren't synced up
        looping = isLooping;
        if(isAnimated && looping) currentFrame = std::rand() % ( frameCount + 1 );
    }
}

// Overriden means use the position reference
void SpriteRenderer::Draw(bool referenced)
{
    // Uses the PlayAnimation function if not looping
    if(!looping) return;
    
    drawRect.x = posRef.x;
    drawRect.y = posRef.y;

    
    ManualRenderer::Draw(referenced);

    // Goes to the next frame 
    Animate();
}

void SpriteRenderer::PlayAnimation(bool referenced)
{
    if(!visible) return;
    if (!thingsToRender[renderIndex])
    {
        print("Can't render from this index")
        return;
    }

    if(referenced)
    {
        drawRect.x = posRef.x;
        drawRect.y = posRef.y;
    }
    else
    {
        drawRect.x = position.x;        
        drawRect.y = position.y;        
    }

    drawRect.w = size.x;
    drawRect.h = size.y;
    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
    SDL_RenderCopyF(renderer, thingsToRender[renderIndex], &sourceRect, &drawRect);
    
    Animate();
}

void SpriteRenderer::Animate()
{
    if(!isAnimated || !thingsToRender[renderIndex]) return;

    sourceRect.x = static_cast<int>(size.x * currentFrame);
    sourceRect.y = 0; 
    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);

    // A timer that goes to the next frame in the animation once it elapses.
    frameTimer += Time::GetDeltaTime();
    if (frameTimer > animSpeed)
    {
        currentFrame++;
        frameTimer = 0;
    }

    // If the animation is looping... set the current frame back to 0... otherwise turn off the animation then reset the current frame
    if (looping && currentFrame > frameCount - 1) currentFrame = 0;
    else if(!looping && currentFrame > frameCount - 1)
    {
        // Turn off the animation but reset it.
        isAnimated = false;
        currentFrame = 0;
    }
}
