#include "Player.h"
#include "Controllers.h"

Player::Player()
{
	const char* runAnims[]
	{
		"Images/run_right1.png",
		"Images/run_right2.png",
		"Images/run_right3.png",
		"Images/run_right4.png",
		"Images/run_left1.png",
		"Images/run_left2.png",
		"Images/run_left3.png",
		"Images/run_left4.png",
	};
	ConfigureRenderer(runAnims);
	renderer.ChangeDestRect(SDL_Rect{10,10,100,100});
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
	return renderer;
	// TODO: insert return statement here
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
