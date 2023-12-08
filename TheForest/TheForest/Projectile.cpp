#include "Projectile.h"

#include "Player.h"

Projectile::Projectile(const std::tuple<EWeaponTypes, float, float, short, float, float>& weapon, const Vector2 pos, const float angle, const Vector2 plyrVelocity,  const bool isSpecial)
{
	position = pos;

	type = std::get<0>(weapon);
	force = std::get<1>(weapon);
	gravityMultiplier = std::get<4>(weapon);
	decelerationRate = 10;

	special = isSpecial;
	
	maxSpeed = 1000;
	maxFallSpeed = 20;

	// Add the player's velocity onto the launch force.
	SetVelocity(plyrVelocity);
	AddForce(Vector2(cos(angle), sin(angle)), force);

	// The repulsion is just the opposite direction the projectile is going
	repulsion = velocity * -1;
	

	switch (std::get<0>(weapon))
	{
		case EWeaponTypes::Seed:
			typePath = special? bigSeedPath : seedPath; 
			break;
			
		case EWeaponTypes::Petal:
			typePath = petalPath; 
			break;
		
		case EWeaponTypes::Sun:
			typePath = sunPath;
			break;
			
		case EWeaponTypes::Thorn:
			typePath = thornPath;
			break;
	}

	renderer = new SpriteRenderer(typePath, position);
	if(typePath == thornPath || typePath == sunPath) renderPivot = {0, renderer->GetRect().y + renderer->GetRect().h / 2};

	
	const Vector2 posVel = position + velocity;
	const Vector2 difference = posVel - position;
	renderRot = (atan2(difference.y, difference.x)) * 180 / std::_Pi;
	renderer->SetRenderAngle(renderRot);
}

void Projectile::Update()
{
	// When using the thorn weapon... it stretches in order to move... (need to get the previous size before deleting)
	const Vector2 drawSize = {renderer->GetRect().w, renderer->GetRect().h};
	
	// The renderer's position reference doesn't work correctly.
	// Makes a new renderer before a position update....
	delete renderer;

	
	// The renderer doesn't work when it's made in the constructor
	renderer = new SpriteRenderer(typePath, position);
	
	renderer->SetRenderAngle(renderRot);
	
	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	if(type != EWeaponTypes::Thorn) position += velocity;
	
	else
	{
		const float stretchRate = special? 15 * 7.5f: 15;

		// Changing the pivot so that the base of the projectile stays close to the player
		renderer->SetSpritePivot(renderer->GetRect().w, renderer->GetRect().h / 2);
		
		// Clamp the height of the drawSize
		renderer->SetDrawSize({drawSize.x + stretchRate, drawSize.y > .1f? drawSize.y - .05f : drawSize.y});
	}
}

void Projectile::Draw()
{
	if(renderer) renderer->Draw(false);
}
