#pragma once

#include <tuple>

#include "Physics.h"
#include "SpriteRenderer.h"

class Projectile : public Physics
{
public:
	Projectile(SDL_FRect projectileRect, bool isSpecial);

	Projectile(Vector2 pos, Vector2 _size, bool isSpecial);
	virtual void Update();
	virtual void Draw();
	
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
};
