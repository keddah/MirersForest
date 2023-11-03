#include "GameCharacter.h"

Character::Character()
{
	rect = SDL_Rect();
}


Character::~Character()
{
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
