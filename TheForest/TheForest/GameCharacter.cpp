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
	// std::cout << "position in char: (" << position.x << ", "<< position.y << ")\n ";
	SetPosition(position);
	renderer.SetSpritePosition(position);
	// print("(" << rect.x << ", " << rect.y << ")\n")
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
	// renderer.Configure(paths, frameCount);
}

void Character::CheckCollisions()
{
}
