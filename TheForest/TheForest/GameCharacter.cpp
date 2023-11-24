#include "GameCharacter.h"

#include <iostream>

// Character::Character() 
// {
// }


Character::Character(const std::vector<std::string>& paths, SDL_FRect& newRect, const std::vector<Collision*>& colliders): Collision(colliders, newRect)
{
	// Sets the player's sprite sheets using their file paths.
	renderer.SetSpriteSheets(paths);

	// Once the images have been loaded from the paths, you can get its image size
	SetRect(GetPosition(), renderer.GetSpriteSize());
}

void Character::Update(float deltaTime)
{
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
