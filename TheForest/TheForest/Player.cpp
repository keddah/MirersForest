#include "Player.h"
#include "Controllers.h"

Player::Player() : Character({"Sprites/testspritesheet.png"}, rect)
{
	ConfigureRenderer({"Sprites/testspritesheet.png"}, 4);
	ChangeMoveState(MovementController::EMovementState::Idle);

	
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


void Player::Update(float deltaTime)
{
	Character::Update(deltaTime);

	controller.Update();

	moveController.Update(deltaTime);
	weaponController.Update(deltaTime);
}

void Player::ChangeMoveState(MovementController::EMovementState state)
{
	switch (state)
	{
	case MovementController::EMovementState::Idle:
		GetRenderer().SetFrameCount(4);
		moveController.ResetSpriteSize(GetRenderer().GetSpriteSize());
		break;

	case MovementController::EMovementState::Moving:
		break;

	case MovementController::EMovementState::CrouchIdle:
		break;

	case MovementController::EMovementState::CrouchMoving:
		break;

	case MovementController::EMovementState::Sliding:
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
