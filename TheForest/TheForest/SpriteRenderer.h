#pragma once

#include "GameManager.h"

class SpriteRenderer
{
public:
	SpriteRenderer(SDL_Rect source, SDL_Rect destination);
	void ChangeSourceRect();
	void ChangeDestRect();


	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

private:
	void Animate();

	const float animSpeed = 1;
	float rotation = 0;
};