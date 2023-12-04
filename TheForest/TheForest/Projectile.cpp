#include "Projectile.h"


Projectile::Projectile(SDL_FRect projectileRect, bool isSpecial)
{
	position = {projectileRect.x, projectileRect.y};
	size = {projectileRect.w, projectileRect.h};
	special = isSpecial;
	
	// The renderer can't be made in the constructor because the size and position could be different each time an object is created 
	renderer = new SpriteRenderer(position, size);
	
	AddForce(Vector2(1,0), force);
}

Projectile::Projectile(const Vector2 pos, const Vector2 _size, const bool isSpecial)
{
	position = pos;
	size = _size;
	special = isSpecial;
	
	// The renderer can't be made in the constructor because the size and position could be different each time an object is created 
	renderer = new SpriteRenderer(position, size);
	
	AddForce(Vector2(1,0), force);
}

void Projectile::Update()
{
	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	position += velocity;

	print("projectile: " << position.x << ", " << position.y)
}

void Projectile::Draw()
{
	renderer->Draw(false);
}

