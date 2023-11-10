#include "SpriteRenderer.h"
#include "RendererSingleton.h"
#include<iostream>

#include "Controllers.h"

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::SpriteRenderer(const char* paths[])
{
	for (int i = 0; i < sizeof(paths); i++) AddTexture(paths[i]);
		
	destinationRect = new SDL_Rect {0, 0, spriteTextures[0].GetImageSize().x, spriteTextures[0].GetImageSize().y};
	sourceRect = new SDL_Rect();
}

void SpriteRenderer::Animate()
{
	// Creating a local texture each frame using the textures that were created in the constructor 
	Image tex = Image(spriteTextures[5].GetImagePath());
	SDL_RenderCopy(GameRenderer::GetRenderer(), tex.GetTexture(), NULL, destinationRect);
}

void SpriteRenderer::AddTexture(const char* path)
{
	spriteTextures.emplace_back(path);
}

void SpriteRenderer::ChangeSourceRect(SDL_Rect newRect)
{
	delete sourceRect;
	
	sourceRect = new SDL_Rect(newRect);
}

void SpriteRenderer::ChangeDestRect(SDL_Rect newRect)
{
	delete destinationRect;
	
	destinationRect = new SDL_Rect(newRect);
}

void SpriteRenderer::Configure(const char* paths[], SDL_Rect source, SDL_Rect destination)
{
	// Get rid of all of the existing textures
	spriteTextures.clear();

	for(int i = 0; i < sizeof(paths); i++)
	{
		AddTexture(paths[i]);
	}

	delete sourceRect;
	delete destinationRect;
	
	sourceRect = new SDL_Rect(source);
	destinationRect = new SDL_Rect(destination);
}


