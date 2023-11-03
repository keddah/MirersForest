#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	Collision();
	Collision(SDL_Rect rect);
	Collision(Vector2 position, Vector2 dimensions);
	~Collision();

	void SetPosition(Vector2 position);
	void SetPosition(int x, int y);

	void SetWidthHeight(Vector2 xy);
	void SetWidthHeight(int x, int y);

	void SetRectangle(SDL_Rect newRect);
	void SetRectangle(Vector2 position, Vector2 dimensions);
	void SetRectangle(Vector2 position, int width, int height);
	void SetRectangle(int x, int y, Vector2 position);
	void SetRectangle(int x, int y, int width, int height);

	bool Overlapping(Collision toCompare);
	bool Contains(Collision toCompare);

private:
	SDL_Rect rect;
};