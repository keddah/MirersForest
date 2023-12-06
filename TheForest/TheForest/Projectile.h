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
	
	Projectile(const std::tuple<EWeaponTypes, float, Vector2, float, short, float, float>& weapon, Vector2 pos, float angle, Vector2 plyrVelocity, bool isSpecial);
	
	virtual void Update();
	virtual void Draw();

	const Vector2& GetRepulsion() const { return repulsion; }
	
private:
	SpriteRenderer* renderer;// = SpriteRenderer(position, {20,20});

	// Is the alternative weapon type (each weapon has 2 types)
	bool special;

	float delay = .8f;
	short ammoCost = 1;
	float rechargeDelay;

	float force = 8;

	Vector2 size {12,12};

	float gravityMultiplier = 1;

	const short blastRadius = 15;
	bool initialised = false;

	Vector2 repulsion;
};
