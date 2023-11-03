#pragma once

#include "GameManager.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	SpriteRenderer(SDL_Rect source, SDL_Rect destination);
	void ChangeSourceRect(SDL_Rect newRect);
	void ChangeDestRect(SDL_Rect newRect);

	void Animate();

	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

private:
	const float animSpeed = 1;
	float rotation = 0;
};