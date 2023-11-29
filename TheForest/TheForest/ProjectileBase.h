#pragma once

#include "Physics.h"
#include "SpriteRenderer.h"

class ProjectileBase : public Physics
{
public:
	ProjectileBase();
	virtual void Update();


protected:
	Vector2 position;
	
	short launchForce = 80;
	float gravityMultiplier;
	float shootTimer;

	SpriteRenderer renderer;

private:

};

class SeedProjectile : public ProjectileBase
{
public:

private:
	float shootDelay;
	const short blastRadius;
};
