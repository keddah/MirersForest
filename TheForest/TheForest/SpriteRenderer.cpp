#include "Renderers.h"

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated): posRef(pos)
{
    imagePath = spritePath;
    isAnimated = animated;

    SDL_Surface* image = SetSprite(imagePath);

    if (!GameWindow::GetRenderer()) print("COuldn't get renderer.")
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

    // Start on a random frame so that the animations aren't synced up
    if(isAnimated) currentFrame = std::rand() % ( frameCount + 1 );
}

// This constructor is used for animated things
SpriteRenderer::SpriteRenderer(const std::vector<std::string>& spritePaths, const Vector2& pos, bool animated): posRef(pos)
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
        if(isAnimated) currentFrame = std::rand() % ( frameCount + 1 );
    }
}

// This constructor is used whenever the thing to render doesn't have a sprite.
SpriteRenderer::SpriteRenderer(const Vector2& pos, Vector2 drawSize): posRef(pos)
{
    size = drawSize;

    // It's position will be set by the owner of this object
    drawRect.w = size.x;
    drawRect.h = size.y;

    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = size.x;
    sourceRect.h = size.y;
}

// Overriden means use the position reference
void SpriteRenderer::Draw(bool referenced)
{
    drawRect.x = posRef.x;
    drawRect.y = posRef.y;

    // print("reference: " << posRef.x << ", " << posRef.y)

    // Need to debug before Drawing so that the box is behind the sprite.
    if(thingsToRender.empty()) DrawRectangle();
    else ManualRenderer::Draw(true);

    // Telling the renderer to use the position set above instead of the position that's set in the StaticRenderer's draw function
    // Also don't try to render anything if there isn't a renderer (instead just do DrawRectangle).
    // if(toRender) ManualRenderer::Draw(true);

    // print("renderer: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)
    // print("renderer: " << drawRect.x << ", " << drawRect.y)

    // Goes to the next frame 
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

    if (currentFrame > frameCount - 1) currentFrame = 0;
}

void SpriteRenderer::DrawRectangle() const
{
    SDL_SetRenderDrawBlendMode(GameWindow::GetRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(GameWindow::GetRenderer(), drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    SDL_RenderFillRectF(GameWindow::GetRenderer(), &drawRect);
}
