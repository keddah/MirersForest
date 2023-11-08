#include "MovementController.h"
#include "PlayerController.h"


MovementController::MovementController(PlayerController& ctrl, Vector2& plyrPos) : controller(ctrl), playerPosition(plyrPos)
{
}


void MovementController::Update(float deltaTime)
{
	ApplyGravity();
	CalculateVelocity(deltaTime);

	Move();
}

void MovementController::CalculateVelocity(float deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(playerPosition.x, playerPosition.y));
	const int dotProd = (playerPosition.x * previousPos.x) + (playerPosition.y * previousPos.y);
	const float displacementAngle = dotProd / (playerPosition.Magnitude() * previousPos.Magnitude());

	const float speed = displacement / deltaTime;

	velocity = direction * speed;
}

void MovementController::CalculateDirection()
{
	// There are only 4 movement inputs
	for(int i = 0; i < 4; i++)
	{
		// 0 = up, 1 = down, 2 = left, 3 = right
		//const bool up = controller.GetMoveInputs()[0];
		//const bool down =controller.GetMoveInputs()[1];
		//const bool left = controller.GetMoveInputs()[2];
		//const bool right = controller.GetMoveInputs()[3];

		//direction = Vector2(left? -1: (right? 1:0), up? -1: (down? 1:0));
	}
}

void MovementController::Move()
{
	if(!canMove) return;

	CalculateDirection();

	velocity += direction * moveSpeed;
	playerPosition += velocity;
	/*print(velocity.x)
	print(velocity.y)*/
}

void MovementController::Jump()
{
	velocity = AddForce(velocity + Vector2(0, 1), jumpForce);
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
