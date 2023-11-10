#pragma once

#include <vector>

#include <SDL.h>
#include "Image.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	
	// For animated things...
	SpriteRenderer(const char* paths[]);

	void AddTexture(const char* path);
	
	void Animate();

	SDL_Rect* GetSourceRectangle() { return sourceRect; }
	SDL_Rect* GetDestinationRectangle() { return destinationRect; }
	void ChangeSourceRect(SDL_Rect newRect);
	void ChangeDestRect(SDL_Rect newRect);

	SpriteRenderer& operator=(const SpriteRenderer& other) {
		this->rotation = other.rotation;
		this->spriteTextures = other.spriteTextures;
		return *this;
	}


private:
	void Configure(const char* paths[], SDL_Rect source, SDL_Rect destination);

	SDL_Rect* sourceRect;
	SDL_Rect* destinationRect;

	const float animSpeed = 1;
	float rotation = 0;

	std::vector<Image> spriteTextures = std::vector<Image>();
};