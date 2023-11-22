#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

void Physics::AddForce(const Vector2 direction, const float force)
{
	velocity += Vector2(direction.x * force, direction.y * force);
}

void Physics::AddForce(const float x, const float y, const float force)
{
	velocity += Vector2(x * force, y * force);
}

void Physics::ApplyGravity(bool lowered, bool accelerated)
{
	if(!gravityOn || grounded) return;

	// If lowered gravity... dampen the gravity.. otherwise .. if accelerated gravity.. strengthen it... otherwise.. normal gravity.
	// (prioritises lowered gravity)
	AddForce(Vector2(0, 1), lowered? gravity * .6f : accelerated? gravity * 1.4f: gravity);
}
