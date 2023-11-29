#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

void Physics::AddForce(const Vector2 direction, const int force)
{
	velocity += Vector2(direction.x * force, direction.y * force);
	velocity -= direction * airFriction.Magnitude();
}

void Physics::AddForce(const int x, const int y, const int force)
{
	velocity += Vector2(x * force, y * force);
	velocity -= Vector2(x, y) * airFriction.Magnitude();
}

void Physics::ApplyGravity(bool lowered, bool accelerated)
{
	if(!gravityOn || grounded) return;

	// If lowered gravity... dampen the gravity.. otherwise .. if accelerated gravity.. strengthen it... otherwise.. normal gravity.
	// (prioritises lowered gravity)
	AddForce(Vector2(0, 1), lowered? currentGravity * .6f : accelerated? currentGravity * 1.4f: currentGravity);
}
