#include "Collider.h"

Collision::Collision(const std::vector<Collision*>& otherColliders, const float x, const float y, const float w, const float h, bool isSolid ) :
debugRenderer(rect), colliders(otherColliders)
{
	solid = isSolid;
	rect = SDL_FRect{x,y,w,h};


	debugRenderer.FillRectangle(debugColour);
}

Collision::Collision(const std::vector<Collision*>& otherColliders, SDL_FRect& _rect, bool isSolid ) :
debugRenderer(rect), colliders(otherColliders)
{
	solid = isSolid;
	rect = _rect;

	debugRenderer.FillRectangle(debugColour);
}

void Collision::Update()
{
	for(auto& collider2: colliders)
	{
		if(this == collider2) continue;

		Overlapping(*collider2);
	}
}

void Collision::Debug()
{
	debugRenderer.FillRectangle(debugColour);
}



// Collider overlaps another collider
bool Collision::Overlapping(const Collision& toCompare)
{
	isOverlapping = SDL_HasIntersectionF(&rect, &toCompare.rect);
	obstructed = isOverlapping && toCompare.solid && solid;

	return isOverlapping;
}

bool Collision::Overlapping(const SDL_FRect& collision1, const Collision& collision2)
{
	return SDL_HasIntersectionF(&collision1, &collision2.rect);
}

bool Collision::Overlapping(const SDL_FRect& toCompare)
{
	isOverlapping = SDL_HasIntersectionF(&rect, &toCompare);

	return isOverlapping;;
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

void Collision::SetRect(SDL_FRect newRect)
{
	rect = newRect;
}

void Collision::SetRect(Vector2 position, Vector2 dimensions)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetRect(Vector2 position, float width, float height)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = width;
	rect.h = height;
}

void Collision::SetRect(float x, float y, Vector2 dimensions)
{
	rect.x = x;
	rect.y = y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetRect(float x, float y, float width, float height)
{
	rect.x = x;
	rect.y = y;

	rect.w = width;
	rect.h = height;
}


const SDL_FRect& Collision::GetContactRect(const Collision& toCompare) const
{
	auto* intersectRect = new SDL_FRect();
	
	SDL_IntersectFRect(&rect, &toCompare.rect, intersectRect);
	return *intersectRect;
}