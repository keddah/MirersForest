#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::GivePowerup()
{
}

void Player::Update(double deltaTime)
{
	moveController.Update(deltaTime);

	rect.x = moveController.position.x;
	rect.y = moveController.position.y;
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
