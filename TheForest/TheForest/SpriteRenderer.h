#pragma once

#include <vector>

#include <SDL.h>
#include "Texture.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	
	// For animated things...
	SpriteRenderer(std::vector<const char*> paths);
	SpriteRenderer(std::vector<const char*> paths, SDL_Rect source, SDL_Rect destination);

	// For basic things
	SpriteRenderer(const char* path);
	SpriteRenderer(const char* path, SDL_Rect source, SDL_Rect destination);

	void AddTexture(const char* path);
	
	void Animate();

	void ChangeSourceRect(SDL_Rect newRect);
	void ChangeDestRect(SDL_Rect newRect);

	SpriteRenderer& operator=(const SpriteRenderer& other) {
		this->rotation = other.rotation;
		this->texturePath = other.texturePath;
		this->spriteTextures = other.spriteTextures;
		return *this;
	}

	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

private:
	void Configure();


	const float animSpeed = 1;
	float rotation = 0;

	char* texturePath;

	std::vector<Texture> spriteTextures = std::vector<Texture>();
};