#include "Collider.h"

Collision::Collision(const float x, const float y, const float w, const float h)  : debugRenderer(rect)
{
	rect = SDL_FRect{x,y,w,h};

	debugRenderer.FillRectangle(debugColour);
}

Collision::Collision(SDL_FRect _rect) : debugRenderer(rect)
{
	rect = _rect;

	debugRenderer.FillRectangle(debugColour);
}

// Collision::Collision(Vector2 position, Vector2 dimensions)
// {
// 	rect.x = position.x;
// 	rect.y = position.y;
//
// 	rect.w = dimensions.x;
// 	rect.h = dimensions.y;
// }

Collision::~Collision()
{
}

void Collision::SetPosition(Vector2 position)
{
	rect.x = position.x;
	rect.y = position.y;
}

void Collision::SetPosition(float x, float y)
{
	rect.x = x;
	rect.y = y;
}

void Collision::SetWidthHeight(Vector2 dimensions)
{
	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetWidthHeight(float w, float h)
{
	rect.w = w;
	rect.h = h;
}

void Collision::SetRectangle(SDL_FRect newRect)
{
	rect = newRect;
}

void Collision::SetRectangle(Vector2 position, Vector2 dimensions)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetRectangle(Vector2 position, float width, float height)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = width;
	rect.h = height;
}

void Collision::SetRectangle(float x, float y, Vector2 dimensions)
{
	rect.x = x;
	rect.y = y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetRectangle(float x, float y, float width, float height)
{
	rect.x = x;
	rect.y = y;

	rect.w = width;
	rect.h = height;
}

bool Collision::Overlapping(const Collision& toCompare)
{
	isOverlapping = SDL_HasIntersectionF(&toCompare.rect, &rect);

	auto* intersectRect = new SDL_FRect();
	SDL_IntersectFRect(&this->rect, &toCompare.rect, intersectRect);
	
	print("rect1: " << intersectRect->x<< ", " << intersectRect->y << ", " << intersectRect->w << ", " << intersectRect->h << ")\n")

	// Checks which part of the rectangle is being obstructed
	if(intersectRect->y >= toCompare.rect.y + toCompare.rect.h) currentObstruction = EObstructionDirection::UP;
	else if(intersectRect->y + intersectRect->h <= toCompare.rect.y) currentObstruction = EObstructionDirection::DOWN;
	
	else if(intersectRect->x >= toCompare.rect.x + toCompare.rect.w) currentObstruction = EObstructionDirection::LEFT;
	else if(intersectRect->x + intersectRect->w <= toCompare.rect.x) currentObstruction = EObstructionDirection::RIGHT;

	return isOverlapping;
}

// Collider overlaps another collider
bool Collision::Overlapping(const SDL_FRect& toCompare)
{
	
	isOverlapping = SDL_HasIntersectionF(&this->rect, &toCompare);

	auto* intersectRect = new SDL_FRect();
	SDL_IntersectFRect(&this->rect, &toCompare, intersectRect);
	
	print("rect1: " << intersectRect->x<< ", " << intersectRect->y << ", " << intersectRect->w << ", " << intersectRect->h << ")\n")
	
	if(intersectRect->y >= toCompare.y + toCompare.h) currentObstruction = EObstructionDirection::UP;
	else if(intersectRect->y + intersectRect->h <= toCompare.y) currentObstruction = EObstructionDirection::DOWN;
	
	else if(intersectRect->x >= toCompare.x + toCompare.w) currentObstruction = EObstructionDirection::LEFT;
	else if(intersectRect->x + intersectRect->w <= toCompare.x) currentObstruction = EObstructionDirection::RIGHT;
	
	return isOverlapping;
}

// Box collision contains another box collider
bool Collision::Contains(const Collision& toCompare) const
{
	const bool inside =
		// Able to compare the position of the rectangle and check if it's inside 'this' rectangle
		((toCompare.rect.x > rect.x) && (toCompare.rect.x < rect.x + rect.w) && 
		((toCompare.rect.y > rect.y)) && (toCompare.rect.y < rect.y + rect.h) &&

		// As long as the rectangle to compare is smaller than the 'this' rectangle and the position is inside
		// the bounds of 'this' rectangle, the rectangle to compare would be in 'this' rectangle 
		toCompare.rect.w < rect.w && toCompare.rect.h < rect.h);
	
	return inside;
			
}

// Box collider contains Vector
bool Collision::Contains(const Vector2 position) const
{
	return  ((position.x > rect.x)) && (position.x < rect.x + rect.w) && 
            ((position.y > rect.y)) && (position.y < rect.y + rect.h);
}

void Collision::Debug()
{
	debugRenderer.FillRectangle(debugColour);
}

const SDL_FRect& Collision::GetContactRect(const Collision& toCompare) const
{
	auto* intersectRect = new SDL_FRect();
	
	SDL_IntersectFRect(&rect, &toCompare.rect, intersectRect);
	return *intersectRect;
}

