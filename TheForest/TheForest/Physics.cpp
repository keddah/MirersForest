#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

Vector2 Physics::AddForce(Vector2 Direction, float force)
{
	return Direction * force;
}

Vector2 Physics::AddForce(int x, int y, float force)
{
	return Vector2(x, y) * force;
}

void Physics::SetGravity(bool on)
{
	gravityOn = on;
}

void Physics::ApplyGravity()
{
	if(gravityOn) AddForce(Vector2(0, -1), Gravity);
		
}
