#pragma once

#define print(x) { std::cout<< x << std::endl; }

#include <iostream>
#include "SpriteRenderer.h"

class Collision
{
public:
	// Collision();
	Collision(const std::vector<Collision*>& otherColliders, float x, float y, float w, float h, bool ground = true, bool isSolid = true);
	Collision(const std::vector<Collision*>& otherColliders, SDL_FRect& rect, bool ground = true,  bool isSolid = true);

	~Collision() = default;

	void Update();
	
	const Vector2& GetPosition() { return {rect.x, rect.y }; }
	void SetPosition(Vector2 position);
	void SetPosition(float x, float y);

	void SetWidthHeight(Vector2 dimensions);
	void SetWidthHeight(float w, float h);

	void SetRect(SDL_FRect newRect);
	void SetRect(Vector2 position, Vector2 dimensions);
	void SetRect(Vector2 position, float width, float height);
	void SetRect(float x, float y, Vector2 dimensions);
	void SetRect(float x, float y, float width, float height);

	void SetSolid(bool isSolid) { solid = isSolid; }
	bool GetSolid() const { return solid; }
	
	bool Overlapping(const Collision& toCompare);
	static bool Overlapping(const SDL_FRect& collision1, const Collision& collision2);
	bool Overlapping(const SDL_FRect& toCompare);
	bool IsOverlapping() const;
	
	bool Contains(const Collision& toCompare) const;
	bool Contains(Vector2 position) const;

	virtual SpriteRenderer& GetRenderer() { return renderer; }
	
	void SetDebugColour(SDL_Rect colour) { debugColour = colour; }
	void Debug();
	bool IsGround() { return isGround; }
	const SDL_FRect& GetRect() const { return rect; }
	const SDL_FRect& GetContactRect(const Collision& toCompare) const;
	bool& IsObstructed() { return obstructed; }

protected:
	SDL_FRect rect;
	SpriteRenderer renderer = SpriteRenderer(rect, 1);

	// Whether this SOLID collider is overlapping with another solid collider 
	bool obstructed = false;


private:
	bool isOverlapping = false;
	bool isGround = true;
	// Whether objects are able to go through it...
	bool solid = true;
	
	SDL_Rect debugColour = SDL_Rect{ 255, 0, 50, 100 };

	// All the colliders
	const std::vector<Collision*>& colliders;
};





class CollisionManager
{
public:
	CollisionManager() = default;

	void Debug() const;
	void Update() const;
	void AddCollider(Collision& toAdd);
	const std::vector<Collision*>& GetColliders() const { return colliders; }
	
private:
	std::vector<Collision*> colliders = std::vector<Collision*>(); 	
	
};
