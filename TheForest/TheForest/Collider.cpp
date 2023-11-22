#include "Collider.h"

Collision::Collision(const std::vector<Collision*>& otherColliders, const float x, const float y, const float w, const float h, bool isSolid ) :
debugRenderer(rect), colliders(otherColliders)
{
	solid = isSolid;
	rect = SDL_FRect{x,y,w,h};

	debugRenderer.FillRectangle(debugColour);
}

Collision::Collision(const std::vector<Collision*>& otherColliders, SDL_FRect _rect, bool isSolid ) :
debugRenderer(rect), colliders(otherColliders)
{
	solid = isSolid;
	rect = _rect;

	debugRenderer.FillRectangle(debugColour);
}

void Collision::Update()
{
	for(const auto& collider2: colliders)
	{
		if(this == collider2) continue;

		Overlapping(*collider2);
	}
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

// Collider overlaps another collider
bool Collision::Overlapping(const Collision& toCompare)
{
	isOverlapping = SDL_HasIntersectionF(&toCompare.rect, &rect);
	
	// If there is an obstruction, use the value that was set.. otherwise there is none
	
	auto* intersectRect = new SDL_FRect();
	SDL_IntersectFRect(&rect, &toCompare.rect, intersectRect);
	obstructed = isOverlapping && toCompare.solid && solid;
	
	//print("this rect: (" << toCompare.rect.x << ", " << toCompare.rect.y << ", " << toCompare.rect.w << ", " << toCompare.rect.h << ")")
	//print("other rect: (" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")\n")
	//
	//print("intersect X: " << intersectRect->x);
	//print("intersect wdith : " << intersectRect->w);
	//print("\n")
	
	// THE PLAYER = toCompare.rect
	// Checks which part of the rectangle is being obstructed
	
	constexpr float tolerance = 4;
	
	// The top
	blockingDirections[0] = intersectRect->y > toCompare.rect.y && obstructed;
	
	// The bottom
	blockingDirections[1] = intersectRect->y == toCompare.rect.y && obstructed;
	
	// The left side
	// blockingDirections[2] = FloatInRange(intersectRect->x + rect.w, toCompare.rect.x, toCompare.rect.x + tolerance);
	blockingDirections[2] = intersectRect->x > toCompare.rect.x && obstructed;
	
	// The right side
	blockingDirections[3] = intersectRect->x == toCompare.rect.x && obstructed;

	
	delete intersectRect;
	return isOverlapping;
}


bool Collision::IsOverlapping() const
{
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