#pragma once

#include <vector>

#include <SDL.h>
#include "Texture.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	
	// For animated things...
	SpriteRenderer(const char* paths[]);
	SpriteRenderer(const char* paths[], SDL_Rect source, SDL_Rect destination);

	void AddTexture(const char* path);
	
	void Animate();

	void ChangeSourceRect(SDL_Rect newRect);
	void ChangeDestRect(SDL_Rect newRect);

	SpriteRenderer& operator=(const SpriteRenderer& other) {
		this->rotation = other.rotation;
		this->spriteTextures = other.spriteTextures;
		return *this;
	}

	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

private:
	void Configure(const char* paths[], SDL_Rect source, SDL_Rect destination);


	const float animSpeed = 1;
	float rotation = 0;

	std::vector<Texture> spriteTextures = std::vector<Texture>();
};