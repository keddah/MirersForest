#include "SpriteRenderer.h"
#include "RendererSingleton.h"
#include<iostream>

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::SpriteRenderer(const char* paths[])
{
	for (int i = 0; i < sizeof(paths); i++) AddTexture(paths[i]);

	sourceRect = SDL_Rect();
	destinationRect = SDL_Rect();
}

SpriteRenderer::SpriteRenderer(const char* paths[], SDL_Rect source, SDL_Rect destination)
{
	for (int i = 0; i < sizeof(paths); i++) AddTexture(paths[i]);

	sourceRect = source;
	destinationRect = destination;
}

void SpriteRenderer::Animate()
{
	SDL_RenderCopy(GameRenderer::GetRenderer(), spriteTextures[0].GetTexture(), NULL, NULL);
}

void SpriteRenderer::AddTexture(const char* path)
{
	spriteTextures.push_back(Texture(path, GameRenderer::GetRenderer()));
}

void SpriteRenderer::ChangeSourceRect(SDL_Rect newRect)
{
	sourceRect = newRect;
}

void SpriteRenderer::ChangeDestRect(SDL_Rect newRect)
{
	destinationRect = newRect;
}

void SpriteRenderer::Configure(const char* paths[], SDL_Rect source, SDL_Rect destination)
{
	// Get rid of all of the existing textures
	spriteTextures.clear();

	for(int i = 0; i < sizeof(paths); i++)
	{
		AddTexture(paths[i]);
	}
	
	sourceRect = source;
	destinationRect = destination;
}


