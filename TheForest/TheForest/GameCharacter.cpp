#include "GameCharacter.h"

#include <iostream>

Character::Character() 
{
}


Character::~Character()
{
}

void Character::Update(float deltaTime)
{
	SetPosition(position);
	renderer.SetSpritePosition(position);
}

void Character::GainHealth()
{
	health.GainHealth();
}

void Character::TakeDamage(float intensity)
{
	health.TakeDamage(intensity);
}

void Character::Death()
{
}

void Character::ConfigureRenderer(const char* paths[], short frameCount)
{
	renderer = SpriteRenderer(paths, position);
}

void Character::CheckCollisions()
{
}
