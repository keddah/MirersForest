#include "Controllers.h"

MovementController::MovementController(PlayerController& ctrl, Vector2& plyrPos, const std::vector<bool>& blockingDirs) :
controller(ctrl), playerPosition(plyrPos), blockedDirections(blockingDirs)
{
	playerPosition.x += 900;
}


void MovementController::Update(float deltaTime)
{
	// Reset the velocity at the start of each frame so that it isn't infinitely increased.
	velocity = Vector2();

	// Since the position is the top left of the image... have to get the bottom.
	// if(playerPosition.y <= 1080 - spriteSize.y) ApplyGravity();
	
	if(playerPosition.y + velocity.y > 1080) playerPosition.y = 0;
	else if(playerPosition.y > 1080) playerPosition.y = 0;
	
	if(playerPosition.x + velocity.x > 1920) playerPosition.x = 0;
	else if(playerPosition.x > 1920) playerPosition.x = 0;

	// slightly reduce gravity if holding down the jump button
	if(!grounded) ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
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

void MovementController::BlockingCollisions()
{
}

void MovementController::Move(float deltaTime)
{
	grounded = blockedDirections[1];

	if(!canMove) return;

	if((controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3]) && currentMoveState != EMovementState::CrouchIdle) currentMoveState = EMovementState::Moving;

	const bool blockedLeft = direction.x < 0 && blockedDirections[2];
	const bool blockedRight = direction.x > 0 && blockedDirections[3];

	// Counteracts the actual input if it's blocked
	if(blockedLeft) velocity.x += moveSpeed;
	if(blockedRight) velocity.x -= moveSpeed;

	velocity.x += moveSpeed * direction.x;
}

void MovementController::Jump()
{
	if(!grounded || blockedDirections[0]) return;

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
