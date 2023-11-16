#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

void Physics::AddForce(const Vector2 direction, const float force)
{
	velocity += Vector2(direction.x * force, direction.y * force);
	// if(velocity.Magnitude() > terminalSpeed) velocity
}

void Physics::AddForce(const float x, const float y, const float force)
{
	velocity += Vector2(x * force, y * force);
}

void Physics::ApplyGravity()
{
	if(!gravityOn) return;
	
	AddForce(Vector2(0, 1), gravity);
}
