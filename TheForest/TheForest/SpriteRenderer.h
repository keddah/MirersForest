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

	void Animate();
	void SetSpritePosition(const Vector2& newPos);
	
	void AddSpriteSheet(const char* path);
	void SetFrameCount(short frames);

	SDL_Rect& GetSourceRectangle() { return sourceRect; }
	SDL_Rect& GetDestinationRectangle() { return destinationRect; }
	void ChangeSourceRect(SDL_Rect newRect);
	void ChangeDestRect(SDL_Rect newRect);

	SpriteRenderer& operator=(const SpriteRenderer& other) {
		this->rotation = other.rotation;
		this->spriteImages = other.spriteImages;
		this->sourceRect = other.sourceRect;
		this->destinationRect = other.destinationRect;
		return *this;
	}


private:
	void Configure(const char* paths[], SDL_Rect source, SDL_Rect destination);

	// (x,y) = the top left corner of the area to crop .. (w,h) = the bottom right corner - the end of the crop.
	SDL_Rect sourceRect;

	// (x,y) = the position .. (w,h) = the size
	SDL_Rect destinationRect;
	Vector2 renderPos;

	// The sprite sheet that's currently being rendered
	short activeAnim = 0;
	short currentFrame = 0;
	double frameTimer = 0;
	float animSpeed = 2;
	float rotation = 0;


	std::vector<Image> spriteImages = std::vector<Image>();
};

