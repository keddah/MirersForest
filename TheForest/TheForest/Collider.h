#pragma once

#define print(x) { std::cout<< x << std::endl; }

#include <iostream>
#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	// Collision();
	Collision(float x, float y, float w, float h);
	Collision(SDL_FRect rect);

	Collision(Vector2 position, Vector2 dimensions);
	~Collision();

	// Whether objects are able to go through it...
	bool solid = true;

	// Whether this SOLID collider is overlapping with another solid collider 
	bool obstructed = false;

	enum class EObstructionDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

	EObstructionDirection currentObstruction = EObstructionDirection::NONE;
	
	bool obstructedUp = false;
	bool obstructedLeft = false;
	
	const Vector2& GetPosition() { return {rect.x, rect.y }; }
	void SetPosition(Vector2 position);
	void SetPosition(float x, float y);

	void SetWidthHeight(Vector2 dimensions);
	void SetWidthHeight(float w, float h);

	void SetRectangle(SDL_FRect newRect);
	void SetRectangle(Vector2 position, Vector2 dimensions);
	void SetRectangle(Vector2 position, float width, float height);
	void SetRectangle(float x, float y, Vector2 dimensions);
	void SetRectangle(float x, float y, float width, float height);
	
	bool Overlapping(const Collision& toCompare) const;
	bool Overlapping(const SDL_FRect& toCompare);
	bool Overlapping(const SDL_FRect& toCompare) const;
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

	void Debug();

	const SDL_FRect& GetRect() const { return rect; }
	const SDL_FRect& GetContactRect(const Collision& toCompare) const;

	bool IsOverlapping() const { return isOverlapping; }
	
protected:
	SDL_FRect rect;

private:
	bool isOverlapping;
	
	SpriteRenderer debugRenderer;
	SDL_Rect debugColour = SDL_Rect{ 255, 0, 50, 100 };
};





class CollisionManager
{
public:
	CollisionManager() = default;

	void Debug() const;
	void Update() const;
	void AddCollider(Collision& toAdd);
	
private:
	std::vector<Collision*> colliders = std::vector<Collision*>(); 	
	
};
