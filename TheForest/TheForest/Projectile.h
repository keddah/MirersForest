#pragma once

#include "Physics.h"
#include "SpriteRenderer.h"

class Projectile : public Physics
{
public:
	enum class EWeaponTypes
	{
		Seed,
		Petal,
		Sun,
		Thorn,
	};
	
	Projectile(EWeaponTypes type, Vector2 pos, bool isSpecial);

	virtual float GetShootDelay() { return shootDelay; }
	virtual void Update();
	virtual void Draw();

	
private:
	SpriteRenderer renderer = SpriteRenderer(_position, {20,20});

	// The weapon type of this object
	EWeaponTypes projType;
	
	
	// Is the alternative weapon type (each weapon has 2 types)
	bool special;

	short ammoCount = 3;
	float rechargeDelay;

	short launchForce;
	
	const short seedForce = 80;
	const short petalForce = 20;
	const short sunForce = 200;
	const short thornForce = 160;

	const float seedDelay = .8f;
	const float petalDelay = .125f;
	const float sunDelay = 2;
	const float thornDelay = 1.2f;
	
	float gravityMultiplier = 1;
	float shootDelay;

	const short blastRadius = 15;

};
