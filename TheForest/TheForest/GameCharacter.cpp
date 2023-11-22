#include "GameCharacter.h"

#include <iostream>

// Character::Character() 
// {
// }


Character::Character(std::vector<std::string> paths, SDL_FRect& newRect, const std::vector<Collision*>& colliders): Collision(colliders, newRect), renderer(paths, rect)
{
	SetRect(GetPosition(), renderer.GetSpriteSize());
}

void Character::Update(float deltaTime)
{
	renderer.SetSpritePosition(Collision::GetPosition());
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
