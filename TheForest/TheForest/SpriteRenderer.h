#pragma once

#include <vector>

#include <SDL.h>
#include "Image.h"

class SpriteRenderer
{
public:
	SpriteRenderer() = default;

	// For animated things...
	SpriteRenderer(const char* paths[], Vector2& pos);
	SpriteRenderer(SDL_Rect& rect);

	void Animate();
	void SetSpritePosition(const Vector2& newPos);
	Vector2 GetSpriteSize();
	
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
		this->fillOn = other.fillOn;
		this->fillColour = other.fillColour;
		return *this;
	}
	
	void Configure(const char* paths[], short frameCount = 4);

	// Primarily for debugging...
	// The rectangle is filled with the inputted color
	void FillRectangle(const int r, const int g, const int b, const int a);
	void FillRectangle(SDL_Rect& colour);
	void UnfillRectangle();

private:
	// (x,y) = the top left corner of the area to crop .. (w,h) = the bottom right corner - the end of the crop.
	SDL_Rect sourceRect = SDL_Rect();

	// (x,y) = the position .. (w,h) = the size
	SDL_Rect destinationRect = SDL_Rect();
	
	Vector2 initReference;
	Vector2& renderPos = initReference;

	// The sprite sheet that's currently being rendered
	short activeAnim = 0;
	short currentFrame = 0;
	double frameTimer = 0;
	float animSpeed = 2;
	float rotation = 0;

	std::vector<Image> spriteImages = std::vector<Image>();

	bool fillOn;
	SDL_Rect fillColour;
};

