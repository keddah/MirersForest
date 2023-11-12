#include "Player.h"
#include "Controllers.h"

Player::Player()
{
	const char* animations[]
	{
		"Sprites/testspritesheet.png",
		"Sprites/run_left1.png",
	};

	ConfigureRenderer(animations, 4);
	ChangeMoveState(MovementController::Idle);
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

SpriteRenderer& Player::GetRenderer()
{
	return Character::GetRenderer();
}


PlayerController& Player::Controller()
{
	return controller;
}

void Player::Update(float deltaTime)
{
	Character::Update(deltaTime);
	
	controller.Update();

	moveController.Update(deltaTime);
	weaponController.Update(deltaTime);
	

	SetPosition(position);
}

void Player::ChangeMoveState(MovementController::EMovementState state)
{
	switch (state)
	{
	case MovementController::Idle:
		GetRenderer().SetFrameCount(4);
		break;

	case MovementController::Moving:
		break;

	case MovementController::Crouching:
		break;

	case MovementController::Sliding:
		break;
	}
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
