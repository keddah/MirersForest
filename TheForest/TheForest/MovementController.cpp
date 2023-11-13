#include "Controllers.h"

#include<iostream>


MovementController::MovementController(PlayerController& ctrl, Vector2& plyrPos) : controller(ctrl), playerPosition(plyrPos)
{
}


void MovementController::Update(float deltaTime)
{
	print(grounded)
	if(!grounded) ApplyGravity();
	if(grounded && velocity.y > 0) velocity.y = 0;
	
	CalculateDirection();
	CalculateVelocity(deltaTime);
	Move();

}

void MovementController::CalculateVelocity(float deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(playerPosition.x, playerPosition.y));
	const int dotProd = (playerPosition.x * previousPos.x) + (playerPosition.y * previousPos.y);
	const float displacementAngle = dotProd / (playerPosition.Magnitude() * previousPos.Magnitude());
	
	const int speed = static_cast<int>(displacement / deltaTime);

	print("direction 1: (" << direction.x << ", " << direction.y << ")\n")
	
	velocity += direction * speed;
	playerPosition += velocity;

	print("velocity 1: (" << velocity.x << ", " << velocity.y << ")\n")
}

void MovementController::CalculateDirection()
{
	direction = Vector2();
	
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
	if(!canMove) return;

	if((controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3]) && currentMoveState != CrouchIdle) currentMoveState = Moving;

	velocity += Vector2(moveSpeed * direction.x,moveSpeed * direction.y);
	playerPosition += velocity;
	print("direction 2: (" << direction.x << ", " << direction.y << ")\n")

	print("velocity 2: (" << velocity.x << ", " << velocity.y << ")\n")
}

void MovementController::Jump()
{
	if(!grounded) return;
	
	AddForce(velocity + Vector2(0, 1), jumpForce);
}

void MovementController::Slide()
{
	Crouch();
	AddForce(velocity + direction, slideSpeed);
}

void MovementController::Crouch()
{
}

void MovementController::Uncrouch()
{
	
}
