#include "Controllers.h"

#include<iostream>


MovementController::MovementController(PlayerController& ctrl, Vector2& plyrPos) : controller(ctrl), playerPosition(plyrPos)
{
}


void MovementController::Update(float deltaTime)
{
	//controller.Update();

	velocity += ApplyGravity();
	playerPosition += velocity;
	
	CalculateVelocity(deltaTime);

	Move();
}

void MovementController::CalculateVelocity(float deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(playerPosition.x, playerPosition.y));
	const int dotProd = (playerPosition.x * previousPos.x) + (playerPosition.y * previousPos.y);
	const float displacementAngle = dotProd / (playerPosition.Magnitude() * previousPos.Magnitude());
	
	const float speed = displacement / deltaTime;
	
	velocity += direction * speed;

	print("velocity 1: (" << direction.x << ", " << direction.y << ")\n")
}

void MovementController::CalculateDirection()
{
	direction = 0;
	
	// There are only 4 movement inputs
	for(int i = 0; i < 4; i++)
	{
		// 0 = up, 1 = down, 2 = left, 3 = right
		const bool up = controller.GetMoveInputs()[0];
		const bool down = controller.GetMoveInputs()[1];
		const bool left = controller.GetMoveInputs()[2];
		const bool right = controller.GetMoveInputs()[3];

		if(up) direction = Vector2(direction.x,-1);
		if(down) direction = Vector2(direction.x,1);
		if(left) direction = Vector2(-1,direction.y);
		if(right) direction = Vector2(1,direction.y);
	}
}

void MovementController::Move()
{
	moving = controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3];
	CalculateDirection();

	if(!canMove) return;

	velocity += direction * moveSpeed;
	playerPosition += velocity;

	// print("controller: (" << playerPosition.x << ", " << playerPosition.y << ")\n")
	print("velocity 2: (" << direction.x << ", " << direction.y << ")\n")
}

void MovementController::Jump()
{
	velocity += AddForce(velocity + Vector2(0, 1), jumpForce);
}

void MovementController::Slide()
{
	Crouch();
}

void MovementController::Crouch()
{
}

void MovementController::Uncrouch()
{
	
}
