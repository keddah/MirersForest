#include "SpriteRenderer.h"

#include "CustomTimer.h"
#include "GameSingletons.h"


SpriteRenderer::SpriteRenderer(const std::string& spritePath, const Vector2& pos, bool animated): posRef(pos)
{
    imagePath = spritePath;
    isAnimated = animated;

    SDL_Surface* image = SetSprite(imagePath);

    if (!GameWindow::GetRenderer()) print("COuldn't get renderer.")
        toRender = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);

    if (!toRender)
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
}

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


void SpriteRenderer::Draw(bool overriden)
{
    drawRect.x = posRef.x;
    drawRect.y = posRef.y;

    // Need to debug before Drawing so that the box is behind the sprite.
    DrawRectangle();

    // Telling the renderer to use the position set above instead of the position that's set in the StaticRenderer's draw function
    // Also don't try to render anything if there isn't a renderer (instead just do DrawRectangle).
    if(toRender) StaticRenderer::Draw(true);

    //print("dest: " << drawRect.x << ", " << drawRect.y << ", " << drawRect.w << ", " << drawRect.h)

    // Goes to the next frame 
    Animate();
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

void SpriteRenderer::DrawRectangle()
{
    SDL_SetRenderDrawColor(GameWindow::GetRenderer(), debugColour.x, debugColour.y, debugColour.w, debugColour.h);
    SDL_RenderFillRectF(GameWindow::GetRenderer(), &drawRect);
}
