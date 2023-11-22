#pragma once

#include<iostream>
#include <string>
#include <vector>
#include <SDL.h>

#include "Image.h"

class SpriteRenderer
{
public:
	SpriteRenderer() = default;

	// For animated things...
	// SpriteRenderer(const char* paths[], Vector2& pos);
	SpriteRenderer(const std::vector<std::string>& paths, const SDL_FRect& rect);
	SpriteRenderer(const SDL_FRect& rect);

	void Animate();
	void SetSpritePosition(const Vector2& newPos);
	Vector2 GetSpriteSize();
	
	void SetFrameCount(short frames);

	SDL_Rect& GetSourceRectangle() { return sourceRect; }
	const SDL_FRect& GetDestinationRectangle() const { return destinationRect; }
	void SetSourceRect(SDL_Rect newRect);

	SpriteRenderer& operator=(const SpriteRenderer& other) {
		this->spriteImages = other.spriteImages;
		this->sourceRect = other.sourceRect;

		this->fillOn = other.fillOn;
		this->fillColour = other.fillColour;

		this->frameTimer = other.frameTimer;
		this->currentFrame = other.currentFrame;
		this->animSpeed = other.animSpeed;
		this->activeAnim = other.activeAnim;
		return *this;
	}
	
	// Primarily for debugging...
	// The rectangle is filled with the inputted color
	void FillRectangle(const int r, const int g, const int b, const int a);
	void FillRectangle(const SDL_Rect& colour);
	void UnfillRectangle();

private:
	// (x,y) = the top left corner of the area to crop .. (w,h) = the bottom right corner - the end of the crop.
	SDL_Rect sourceRect = SDL_Rect();

	// (x,y) = the position .. (w,h) = the size
	const SDL_FRect& destinationRect;

	// The sprite sheet that's currently being rendered
	short activeAnim = 0;
	short currentFrame = 0;
	float frameTimer = 0;
	float animSpeed = 2;

	std::vector<Image> spriteImages = std::vector<Image>();

	bool fillOn;
	SDL_Rect fillColour;
};

