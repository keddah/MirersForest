#include "GameCharacter.h"

#include <iostream>

// Character::Character() 
// {
// }


Character::Character(std::vector<std::string> paths, SDL_FRect& newRect): renderer(paths, newRect), Collision(newRect)
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

void Character::ConfigureRenderer(std::vector<std::string> paths, short frameCount)
{
	renderer = SpriteRenderer(std::move(paths), rect);
}

void Character::CheckCollisions()
{
}
