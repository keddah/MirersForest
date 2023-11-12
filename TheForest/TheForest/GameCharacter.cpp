#include "GameCharacter.h"

#include <iostream>

Character::Character() 
{
	SetRectangle(0,0, Vector2(renderer.GetDestinationRectangle().x, renderer.GetDestinationRectangle().y));
}


Character::~Character()
{
}

void Character::Update(float deltaTime)
{
	std::cout << "position in char: (" << position.x << ", "<< position.y << ")\n ";
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
	renderer = SpriteRenderer(paths);
	renderer.SetFrameCount(frameCount);
}