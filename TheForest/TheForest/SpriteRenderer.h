#pragma once

#include "GameManager.h"

class SpriteRenderer
{
public: 
	SpriteRenderer(SDL_RECT);
	void ChangeSourceRect();
	void ChangeDestRect();

private:
	void Animate();
	
	const float animSpeed = 1;
	float rotation = 0;
};