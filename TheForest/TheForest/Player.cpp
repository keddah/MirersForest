#include "Player.h"
#include "MovementController.h"
#include "WeaponController.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::GivePowerup()
{
}

Vector2& Player::GetPosition()
{
	return position;
}

PlayerController Player::Controller()
{
	return controller;
}

void Player::Update(float deltaTime)
{
	moveController.Update(deltaTime);

	rect.x = position.x;
	rect.y = position.y;
}

void Player::Draw()
{
	Character::Draw();
}

void Player::GainHealth()
{
	health.GainHealth();
}

void Player::TakeDamage(float damageIntensity)
{
	health.TakeDamage(damageIntensity);
}

void Player::Death()
{
}
