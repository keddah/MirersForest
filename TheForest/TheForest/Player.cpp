#include "Player.h"

Player::Player()
{
	moveController = MovementController(this);
	weaponController = WeaponController(this);
}

Player::~Player()
{
}

void Player::GivePowerup()
{
}

PlayerController Player::Controller()
{
	return controller;
}

void Player::Update(double deltaTime)
{
	moveController.Update(deltaTime);

	rect.x = moveController.GetPosition().x;
	rect.y = moveController.GetPosition().y;
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
