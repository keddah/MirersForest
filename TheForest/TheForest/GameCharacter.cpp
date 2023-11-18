#include "GameCharacter.h"

#include <iostream>

// Character::Character() 
// {
// }


Character::Character(std::vector<std::string> paths, SDL_FRect& newRect): Collision(newRect), renderer(paths, newRect)
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

void Character::SetFrameCount(const short frameCount)
{
	renderer.SetFrameCount(frameCount);
}

void Character::CheckCollisions()
{
}
