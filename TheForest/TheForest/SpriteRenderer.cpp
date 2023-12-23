#include "Renderers.h"

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated, bool isLooping): posRef(pos)
{
    imagePath = spritePath;
    isAnimated = animated;

    SDL_Surface* image = SetSprite(imagePath);

    if (!GameWindow::GetRenderer())
    {
        print("COuldn't get renderer.")
        return;
    }

    thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image));

    if (!thingsToRender[renderIndex])
    {
        print("nothing to render.")
        return;
    }

    size.x = isAnimated? image->w / frameCount: image->w;
    size.y = image->h;

    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = size.x;
    sourceRect.h = size.y;

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

    for (const auto& path : spritePaths)
    {
        SDL_Surface* image = ManualRenderer::SetSprite(path);
        
        if (!GameWindow::GetRenderer()) print("COuldn't get renderer.")
        else thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image));

        if (!thingsToRender[renderIndex])
        {
            print("nothing to render.")
                return;
        }
        size.x = isAnimated? image->w / frameCount: image->w;
        size.y = image->h;

        // It's position will be set by the owner of this object
        drawRect.w = size.x;
        drawRect.h = size.y;

        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = size.x;
        sourceRect.h = size.y;

        SDL_FreeSurface(image);

        // Start on a random frame so that the animations aren't synced up
        looping = isLooping;
        if(isAnimated && looping) currentFrame = std::rand() % ( frameCount + 1 );
    }
}

// Overriden means use the position reference
void SpriteRenderer::Draw(bool referenced)
{
    if(!looping) return;
    
    drawRect.x = posRef.x;
    drawRect.y = posRef.y;

    
    // print("reference: " << posRef.x << ", " << posRef.y)
    ManualRenderer::Draw(referenced);

    // Telling the renderer to use the position set above instead of the position that's set in the StaticRenderer's draw function
    // Also don't try to render anything if there isn't a renderer (instead just do DrawRectangle).
    // if(toRender) ManualRenderer::Draw(true);

    // print("renderer: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)
    // print("renderer: " << drawRect.x << ", " << drawRect.y)

    // Goes to the next frame 
    Animate();
}

void SpriteRenderer::PlayAnimation(bool referenced)
{
    if(!visible) return;
    if(!thingsToRender[renderIndex]) print("Can't render from this index")

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
    
    SDL_RenderCopyF(GameWindow::GetRenderer(), thingsToRender[renderIndex], &sourceRect, &drawRect);
    
    Animate();
}

void SpriteRenderer::Animate()
{
    if(!isAnimated || !thingsToRender[renderIndex]) return;

    sourceRect.x = size.x * currentFrame;
    sourceRect.y = 0; 
    sourceRect.w = size.x;
    sourceRect.h = size.y;

    frameTimer += Time::GetDeltaTime();
    if (frameTimer > animSpeed)
    {
        currentFrame++;
        frameTimer = 0;
    }

    if (looping && currentFrame > frameCount - 1) currentFrame = 0;
    else if(!looping && currentFrame > frameCount - 1)
    {
        // Turn off the animation but reset it.
        isAnimated = false;
        currentFrame = 0;
    }
}
