#include "GameCharacter.h"

Character::Character() 
{
}


Character::~Character()
{
}

void Character::Draw()
{
	renderer.Animate();
}

void Character::GainHealth()
{
	health.GainHealth();
}

void Character::TakeDamge(float intensity)
{
	health.TakeDamage(intensity);
}

void Character::Death()
{
}
