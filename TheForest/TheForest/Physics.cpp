#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

void Physics::AddForce(const Vector2 direction, const int force)
{
	velocity += Vector2(force * direction.x, force * direction.y);

	// if(velocity.Magnitude() > terminalSpeed) velocity
}

void Physics::AddForce(const int x, const int y, const int force)
{
	velocity += Vector2(force * x, force * y);
}

void Physics::ApplyGravity()
{
	if(!gravityOn) return;
	
	AddForce(Vector2(0, 1), gravity);
}
