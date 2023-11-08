#include "SpriteRenderer.h"
#include "RendererSingleton.h"


SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::SpriteRenderer(std::vector<const char*> paths)
{
	for (const char* path : paths) AddTexture(path);

	sourceRect = SDL_Rect();
	destinationRect = SDL_Rect();
}

SpriteRenderer::SpriteRenderer(std::vector<const char*> paths, SDL_Rect source, SDL_Rect destination)
{
	for (const char* path : paths) AddTexture(path);

	sourceRect = source;
	destinationRect = destination;
}

SpriteRenderer::SpriteRenderer(const char* path)
{
	AddTexture(path);

	sourceRect = SDL_Rect();
	destinationRect = SDL_Rect();
}

SpriteRenderer::SpriteRenderer(const char* path, SDL_Rect source, SDL_Rect destination)
{
	AddTexture(path);
	
	sourceRect = source;
	destinationRect = destination;
}

void SpriteRenderer::Animate()
{
}

void SpriteRenderer::AddTexture(const char* path)
{
	spriteTextures.push_back(Texture(path, GameRenderer::GetRenderer()));
}

void SpriteRenderer::ChangeSourceRect(SDL_Rect newRect)
{
}

void SpriteRenderer::ChangeDestRect(SDL_Rect newRect)
{
}

void SpriteRenderer::Configure(std::vector<const char*> paths, SDL_Rect source, SDL_Rect destination)
{
	texturePath = paths;
}


