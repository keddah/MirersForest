#pragma once

#define print(x) { std::cout<< x << std::endl; }

#include <iostream>
#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	Collision();
	Collision(float x, float y, float w, float h);
	Collision(SDL_FRect rect);

	Collision(Vector2 position, Vector2 dimensions);
	~Collision();

	// Whether objects are able to go through it...
	bool solid = true;

	// Whether this SOLID collider is overlapping with another solid collider 
	bool obstructed = false;
	
	void SetPosition(Vector2 position);
	void SetPosition(float x, float y);

	void SetWidthHeight(Vector2 xy);
	void SetWidthHeight(float x, float y);

	void SetRectangle(SDL_FRect newRect);
	void SetRectangle(Vector2 position, Vector2 dimensions);
	void SetRectangle(Vector2 position, float width, float height);
	void SetRectangle(float x, float y, Vector2 position);
	void SetRectangle(float x, float y, float width, float height);
	
	bool Overlapping(const Collision& toCompare) const;
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

	bool IsDebugging() const { return debugging; }
	void Debug();

	const SDL_FRect& GetRect() { return rect; }

protected:
	SDL_FRect rect;
	Collision& ReturnSelf() { return *this; }


private:
	bool debugging;
	
	SpriteRenderer debugRenderer;
	SDL_Rect debugColour = SDL_Rect{ 231, 23, 133, 1 };
};
