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

void Character::ConfigureRenderer(std::vector<const char*> paths, SDL_Rect source, SDL_Rect destination)
{
	renderer = SpriteRenderer(paths, source, destination);
}

void Character::ConfigureRenderer()
{
	SpriteRenderer(paths, source, destination)
}
