#include "Collider.h"

Collision::Collision()
{
	rect = SDL_Rect();
}

Collision::Collision(SDL_Rect _rect)
{
	rect = _rect;
}

Collision::Collision(Vector2 position, Vector2 dimensions)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

Collision::~Collision()
{
}

void Collision::SetPosition(Vector2 position)
{
	rect.x = position.x;
	rect.y = position.y;
}

void Collision::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Collision::SetWidthHeight(Vector2 dimensions)
{
	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetWidthHeight(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

void Collision::SetRectangle(SDL_Rect newRect)
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

void Collision::SetRectangle(Vector2 position, int width, int height)
{
	rect.x = position.x;
	rect.y = position.y;

	rect.w = width;
	rect.h = height;
}

void Collision::SetRectangle(int x, int y, Vector2 dimensions)
{
	rect.x = x;
	rect.y = y;

	rect.w = dimensions.x;
	rect.h = dimensions.y;
}

void Collision::SetRectangle(int x, int y, int width, int height)
{
	rect.x = x;
	rect.y = y;

	rect.w = width;
	rect.h = height;
}

// Collider overlaps another collider
bool Collision::Overlapping(const Collision& toCompare) const
{
	const bool overlap =
		// Compare to the horizontal line - if ths position is greater or equal to anywhere along 'this' line ... otherwise,
		((toCompare.rect.x >= rect.x && toCompare.rect.x < rect.x + rect.w) ||
			
		// Is the line toCompare anywhere along the line of 'this' line 
		((toCompare.rect.x + toCompare.rect.w >= rect.x) && (toCompare.rect.x + toCompare.rect.w <= rect.x + rect.w)) ||

		// Compare to the vertical line - if ths position is greater or equal to anywhere along 'this' line....
		(toCompare.rect.y >= rect.y && toCompare.rect.y < rect.y + rect.h) ||

		// Compare to the vertical line
		((toCompare.rect.y + toCompare.rect.h >= rect.y) && (toCompare.rect.y + toCompare.rect.h <= rect.y + rect.h)));
		
	return overlap;
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
	return  ((position.x >= rect.x)) && (position.x <= rect.x + rect.w) && 
            ((position.y >= rect.y)) && (position.y <= rect.y + rect.h);
}
