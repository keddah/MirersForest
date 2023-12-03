#include "Projectile.h"

Projectile::Projectile(const EWeaponTypes type, const Vector2 pos, const bool isSpecial)
{
	_position = pos;
	special = isSpecial;

	projType = type;

	switch (projType)
	{
		case EWeaponTypes::Seed:
			launchForce = special? seedForce * 2 : seedForce;
			shootDelay = seedDelay;
			break;
			
		case EWeaponTypes::Petal:
			launchForce = petalForce;
			shootDelay = special? petalDelay * 5: petalDelay;
			break;
			
		case EWeaponTypes::Sun:
			launchForce = special? 0 : sunForce;
			shootDelay = sunDelay;
			break;
			
		case EWeaponTypes::Thorn:
			launchForce = thornForce;
			shootDelay = thornDelay;
			break;
	}

	// Launch as soon as it's created.
	AddForce(Vector2(1,0), launchForce);
}

void Projectile::Update()
{
	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	_position += velocity;
}

void Projectile::Draw()
{
	renderer.Draw();
}