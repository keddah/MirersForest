#include "Projectile.h"

#include "Player.h"

Projectile::Projectile(const std::tuple<EWeaponTypes, float, Vector2, float, short, float, float>& weapon, const Vector2 pos, const float angle, const Vector2 plyrVelocity,  const bool isSpecial)
{
	position = pos;
	
	size = std::get<2>(weapon);
	force = std::get<1>(weapon);
	gravityMultiplier = std::get<5>(weapon);
	decelerationRate = 10;
	
	special = isSpecial;

	maxSpeed = 1000;
	maxFallSpeed = 20;

	// The renderer can't be made in the constructor because the size and position could be different each time an object is created 
	renderer = new SpriteRenderer(position, size);
	initialised = true;

	// Add the player's velocity onto the launch force.
	SetVelocity(plyrVelocity);
	AddForce(Vector2(cos(angle), sin(angle)), force);

	repulsion = velocity * -1;
	
	print(velocity.x);
}

void Projectile::Update()
{
	// The renderer's position reference doesn't work correctly.
	// Makes a new renderer before a position update....
	delete renderer;
	renderer = new SpriteRenderer(position, size);
	
	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	position += velocity;
}

void Projectile::Draw()
{
	if(initialised) renderer->Draw(false);
}

