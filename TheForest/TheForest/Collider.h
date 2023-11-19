#pragma once

#define print(x) { std::cout<< x << std::endl; }

#include <tuple>
#include <iostream>
#include "Vector2.h"
#include "SpriteRenderer.h"

class Collision
{
public:
	// Collision();
	Collision(float x, float y, float w, float h);
	Collision(SDL_FRect rect);

	~Collision() = default;

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

	void SetSolid(bool isSolid) { solid = isSolid; }
	bool GetSolid() const { return solid; }
	
	bool Overlapping(const Collision& toCompare);
	bool IsOverlapping() const;
	
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

	// Returns a tuple that contains whether or not there is an obstruction and the direction of the obstruction.
	// const std::tuple<bool, EObstructionDirection>& GetObstruction() { return obstruction; }
	
	void Debug();

	const SDL_FRect& GetRect() const { return rect; }
	const SDL_FRect& GetContactRect(const Collision& toCompare) const;

	
protected:
	SDL_FRect rect;
	// The direction of contact
	std::vector<bool> blockingDirections = std::vector<bool>(4);
	bool unObstructed;

private:
	bool isOverlapping;

	// Whether objects are able to go through it...
	bool solid = true;

	// Whether this SOLID collider is overlapping with another solid collider 
	bool obstructed = false;
	
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
