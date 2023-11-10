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

void Character::ConfigureRenderer(const char* paths[])
{
	renderer = SpriteRenderer(paths);
}