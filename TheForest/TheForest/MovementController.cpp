#include "Controllers.h"

MovementController::MovementController(PlayerController& ctrl, Vector2& plyrPos) : controller(ctrl), playerPosition(plyrPos)
{
}


void MovementController::Update(float deltaTime)
{
	// Reset the velocity at the start of each frame so that it isn't infinitely increased.
	velocity = Vector2();

	// Since the position is the top left of the image... have to get the bottom.
	if(playerPosition.y <= 1080 - spriteSize.y) ApplyGravity();
	
	if(playerPosition.y + velocity.y > 1080) playerPosition.y = 0;
	else if(playerPosition.y > 1080) playerPosition.y = 0;
	
	if(playerPosition.x + velocity.x > 1920) playerPosition.x = 0;
	else if(playerPosition.x > 1920) playerPosition.x = 0;
	// if(!grounded) ApplyGravity();
	CalculateDirection();
	CalculateVelocity(deltaTime);
	Move(deltaTime);

	playerPosition += velocity;
}

void MovementController::ResetSpriteSize(const Vector2& newSize)
{
	spriteSize = newSize;
}

void MovementController::CalculateVelocity(float deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(playerPosition.x, playerPosition.y));
	const int dotProd = (playerPosition.x * previousPos.x) + (playerPosition.y * previousPos.y);
	const float displacementAngle = dotProd / (playerPosition.Magnitude() * previousPos.Magnitude());
	
	const int speed = static_cast<int>(displacement / deltaTime);

	// print("direction 1: (" << direction.x << ", " << direction.y << ")\n")
	
	// print("velocity 1: (" << velocity.x << ", " << velocity.y << ")\n")
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

		if(up) Jump();
		if(down) Crouch();
		
		if(left) direction = Vector2(-1,direction.y);
		if(right) direction = Vector2(1,direction.y);
	}
}

// void MovementController::BlockingCollisions(const std::tuple<bool, Collision::EObstructionDirection>& obstruction)
// {
// 	// print("velocity 1: (" << velocity.x << ", " << velocity.y << ")\n")
//
// 	blockedDirection = EBlockedDirection::NONE;
// 	
// 	// If there's no obstruction... don't do anything
// 	if(!std::get<bool>(obstruction)) return;
// 	
// 	if(std::get<Collision::EObstructionDirection>(obstruction) == Collision::EObstructionDirection::UP)
// 	{
// 		blockedDirection = EBlockedDirection::UP;
// 	}
//
// 	if(std::get<Collision::EObstructionDirection>(obstruction) == Collision::EObstructionDirection::DOWN)
// 	{
// 		blockedDirection = EBlockedDirection::DOWN;
// 		grounded = true;
// 	}
//
// 	if(std::get<Collision::EObstructionDirection>(obstruction) == Collision::EObstructionDirection::LEFT)
// 	{
// 		blockedDirection = EBlockedDirection::LEFT;
// 	}
//
// 	if(std::get<Collision::EObstructionDirection>(obstruction) == Collision::EObstructionDirection::RIGHT)
// 	{
// 		blockedDirection = EBlockedDirection::RIGHT;
// 	}
//
// 	// grounded = blockedDirection == EBlockedDirection::DOWN;
// }

void MovementController::BlockingCollisions(bool up, bool down, bool left, bool right)
{
	unObstructed = !up && !down && !left && !right;
	
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;

	// if(up) print("up")
	// if(down) print("down")
	// if(left) print("left")
	// if(right) print("right")
	
	
	grounded = down;
}

void MovementController::Move(float deltaTime)
{
	if(!canMove) return;

	if((controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3]) && currentMoveState != EMovementState::CrouchIdle) currentMoveState = EMovementState::Moving;

	// The delta time is inconsistent... the velocity spikes sometimes.....
	if(left && direction.x < 0) velocity += Vector2(moveSpeed * direction.x, 0);// * deltaTime;
	if(right && direction.x > 0)velocity += Vector2(moveSpeed * direction.x, 0);// * deltaTime;

	
	// print("direction 2: (" << direction.x << ", " << direction.y << ")\n")

	// print("velocity 2: (" << velocity.x << ", " << velocity.y << ")\n")
}

void MovementController::Jump()
{
	if(!grounded) return;

	velocity.y += jumpForce;
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
