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


bool Collision::Overlapping(Collision toCompare)
{
	return false;
}

bool Collision::Contains(Collision toCompare)
{
	return false;
}
