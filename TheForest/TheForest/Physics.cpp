#include "Physics.h"

bool Physics::IsGrounded()
{
	return false;
}

void Physics::AddForce(float force)
{
}

void Physics::SetGravity(bool on)
{
	gravityOn = on;
}

void Physics::ApplyGravity()
{
	while(gravityOn)
	{
		AddForce(Gravity);
	}
}
