#include "Player.h"
#include "Controllers.h"

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
	controller.Update();

	moveController.Update(deltaTime);
	weaponController.Update(deltaTime);

	SetPosition(position);
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
