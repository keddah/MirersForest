#pragma once

#include <string>
#include <vector>

#include "Image.h"

class SpriteRenderer
{
public:
	SpriteRenderer() = default;

	// Frame count is for animated things...
	SpriteRenderer(const SDL_FRect& rect, bool animated);

	void Draw();
	Vector2 GetSpriteSize();
	
	void SetFrameCount(short frames = 1);

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

	// Deletes all of the elements in the spriteImages vector and emplace a new one using this path.
	// (used when creating tiles)
	void SetSprite(const std::string& path);
	void SetIsAnimated(const bool animated) { isAnimated = animated; }
	void SetImage(const Image& newImage);

	// Pass in an array of image paths. Done to set the animations to choose from.  
	// (used when creating characters)
	void SetSpriteSheets(const std::vector<std::string>& paths);
	
	void FillRectangle(const int r, const int g, const int b, const int a);
	void FillRectangle(const SDL_Rect& colour);
	void UnFillRectangle();

private:
	// (x,y) = the top left corner of the area to crop .. (w,h) = the bottom right corner - the end of the crop.
	SDL_Rect sourceRect = SDL_Rect();

	// (x,y) = the position .. (w,h) = the size
	const SDL_FRect& destinationRect;

	// The sprite sheet that's currently being rendered
	bool isAnimated;
	short activeAnim = 0;
	short frameCount = 1;
	short currentFrame = 0;
	float frameTimer = 0;
	float animSpeed = 2;

	std::vector<Image> spriteImages = std::vector<Image>();

	bool fillOn;
	SDL_Rect fillColour;
};

