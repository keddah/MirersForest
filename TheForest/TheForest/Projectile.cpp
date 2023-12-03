#include "Projectile.h"


Projectile::Projectile(const EWeaponTypes type, const Vector2 pos, bool isSpecial)
{
	special = isSpecial;
	projType = type;

	position = pos;
	
	switch (projType)
	{
		// Tuple order = Type->Force->Size->Delay->ammo
		case EWeaponTypes::Seed:
			weapon = std::make_tuple(EWeaponTypes::Seed, (special? seedForce * 2 : seedForce), special? seedSize * 2 : seedSize, seedDelay, seedAmmo);
			break;
			
		case EWeaponTypes::Petal:
			weapon = std::make_tuple(EWeaponTypes::Petal, petalForce, petalSize, special? petalDelay * 5: petalDelay, petalAmmo);
			break;
			
		case EWeaponTypes::Sun:
			weapon = std::make_tuple(EWeaponTypes::Sun, special? 0 : sunForce, sunSize, sunDelay, sunAmmo);
			break;
			
		case EWeaponTypes::Thorn:
			weapon = std::make_tuple(EWeaponTypes::Thorn, thornForce, thornSize, thornDelay, thornAmmo);
			break;
	}

	renderer = new SpriteRenderer(position, std::get<Vector2>(weapon));
}

void Projectile::Launch()
{
	AddForce(Vector2(1,0), std::get<1>(weapon));
}

void Projectile::Update()
{
	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	position += velocity;

	// print("projectile: " << _position.x << ", " << _position.y)

}

void Projectile::Draw()
{
	renderer->Draw(false);
}

