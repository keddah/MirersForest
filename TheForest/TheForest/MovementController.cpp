#include "MovementController.h"

#define print(x){std::cout << (x) << std::endl;}


MovementController::MovementController(Player*& plyr)
{
	player = plyr;
}

void MovementController::Update(double deltaTime)
{
	ApplyGravity();
	CalculateVelocity(deltaTime);

	Move();
}

Vector2& MovementController::GetPosition()
{
	return position;
}

void MovementController::CalculateVelocity(double deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(position.x, position.y));
	const float dotProd = (position.x * previousPos.x) + (position.y * previousPos.y);
	const float displacementAngle = dotProd / position.Magnitude() * previousPos.Magnitude();

	const float speed = displacement / deltaTime;

	velocity = direction * speed;
}

void MovementController::CalculateDirection()
{
	// There are only 4 movement inputs
	for(int i = 0; i < 4; i++)
	{
		// 0 = up, 1 = down, 2 = left, 3 = right
		const bool up = player->Controller().GetMoveInputs()[0];
		const bool down = player->Controller().GetMoveInputs()[1];
		const bool left = player->Controller().GetMoveInputs()[2];
		const bool right = player->Controller().GetMoveInputs()[3];

		direction = Vector2(left? -1: (right? 1:0), up? -1: (down? 1:0));
	}
}

void MovementController::Move()
{
	if(!canMove) return;

	CalculateDirection();

	velocity += direction * moveSpeed;
	print(velocity.x);
	print(velocity.y);
}

void MovementController::Jump()
{
	velocity = AddForce(velocity + Vector2(0, 2), jumpForce);
}

void MovementController::Slide()
{
}

void MovementController::Crouch()
{
}
