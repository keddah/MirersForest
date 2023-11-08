#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	Collision();
	Collision(SDL_Rect rect);
	Collision operator=(const SDL_Rect& other) { return Collision(other); }

	Collision(Vector2 position, Vector2 dimensions);
	~Collision();

	virtual void SetPosition(Vector2 position);
	virtual void SetPosition(int x, int y);

	virtual void SetWidthHeight(Vector2 xy);
	virtual void SetWidthHeight(int x, int y);

	virtual void SetRectangle(SDL_Rect newRect);
	virtual void SetRectangle(Vector2 position, Vector2 dimensions);
	virtual void SetRectangle(Vector2 position, int width, int height);
	virtual void SetRectangle(int x, int y, Vector2 position);
	virtual void SetRectangle(int x, int y, int width, int height);
	
	bool Overlapping(const Collision& toCompare) const;
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

protected:
	SDL_Rect rect;
};
