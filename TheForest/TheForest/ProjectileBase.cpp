#include "ProjectileBase.h"

ProjectileBase::ProjectileBase() : renderer(position, {20,20})
{

}

void ProjectileBase::Update()
{
	currentGravity = gravity * gravityMultiplier;
	ApplyGravity();

	position += velocity;
}
