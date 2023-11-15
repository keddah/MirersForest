#pragma once

#define print(x) { std::cout<< x << std::endl; }

#include <iostream>
#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	Collision();
	Collision(int x, int y, int w, int h);
	Collision(SDL_Rect rect);

	Collision(Vector2 position, Vector2 dimensions);
	~Collision();

	// Whether objects are able to go through it...
	bool solid = true;

	// Whether this SOLID collider is overlapping with another solid collider 
	bool obstructed = false;
	
	void SetPosition(Vector2 position);
	void SetPosition(int x, int y);

	void SetWidthHeight(Vector2 xy);
	void SetWidthHeight(int x, int y);

	void SetRectangle(SDL_Rect newRect);
	void SetRectangle(Vector2 position, Vector2 dimensions);
	void SetRectangle(Vector2 position, int width, int height);
	void SetRectangle(int x, int y, Vector2 position);
	void SetRectangle(int x, int y, int width, int height);
	
	bool Overlapping(const Collision& toCompare) const;
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

	bool IsDebugging() const { return debugging; }
	void Debug();

	const SDL_Rect& GetRect() { return rect; }

protected:
	SDL_Rect rect;
	Collision& ReturnSelf() { return *this; }


private:
	bool debugging;
	
	SpriteRenderer debugRenderer;
	SDL_Rect debugColour = SDL_Rect{ 231, 23, 133, 1 };
};
