#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
	sourceRect = SDL_Rect();
	destinationRect = SDL_Rect();
}

SpriteRenderer::SpriteRenderer(SDL_Rect source, SDL_Rect destination)
{
	sourceRect = source;
	destinationRect = destination;
}

void SpriteRenderer::Animate()
{
}

void SpriteRenderer::ChangeSourceRect(SDL_Rect newRect)
{
}

void SpriteRenderer::ChangeDestRect(SDL_Rect newRect)
{
}


