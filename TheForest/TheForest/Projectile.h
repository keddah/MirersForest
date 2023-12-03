#pragma once

#include <tuple>

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
	void Launch();
	
	virtual float GetShootDelay() { return std::get<3>(weapon); }
	virtual void Update();
	virtual void Draw();
	
private:
	SpriteRenderer* renderer;// = SpriteRenderer(position, {20,20});

	// The weapon type of this object
	EWeaponTypes projType;

	
	// Is the alternative weapon type (each weapon has 2 types)
	bool special;

	short currentAmmo = 3;
	float rechargeDelay;

	const int seedForce = 8;
	const int petalForce = 8;
	const int sunForce = 8;
	const int thornForce = 8;

	const float seedDelay = .8f;
	const float petalDelay = .125f;
	const float sunDelay = 2;
	const float thornDelay = 1.2f;

	
	const Vector2 seedSize {12,12};
	const Vector2 petalSize {6,6};
	const Vector2 sunSize {400,24};
	const Vector2 thornSize {250,10};

	// Special uses 2
	const short seedAmmo = 3;

	// Special uses 10
	const short petalAmmo = 30;

	// Special uses 2
	const short sunAmmo = 6;

	// Always uses 1
	const short thornAmmo = 5;
	
	float gravityMultiplier = 1;

	const short blastRadius = 15;

	// The weapon type .. The force .. The size .. The Delay .. The ammo count
	// When Getting :
	// Type = 0 .. Force = 1 .. Size = 2 .. Delay = 3 .. Ammo = 4
	std::tuple<EWeaponTypes, int, Vector2, float, short> weapon;
};
