#include "Controllers.h"

MovementController::MovementController(PlayerController& ctrl, Collision& _playerCollider, const std::vector<Collision*>& colliders) :
controller(ctrl), playerCollider(_playerCollider), levelColliders(colliders)
{
}


void MovementController::Update(float deltaTime)
{
	// Reset the velocity at the start of each frame so that it isn't infinitely increased.
	velocity = Vector2();

	Move(deltaTime);

	// slightly reduce gravity if holding down the jump button // slightly increase gravity when holding crouch
	ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
	ApplyVelocity();
	//playerCollider.SetPosition(playerCollider.GetPosition() + (falling? velocity : Vector2(velocity.x, 0)));

	//CalculateVelocity(deltaTime);
}

void MovementController::ResetSpriteSize(const Vector2& newSize)
{
	spriteSize = newSize;
}

void MovementController::CalculateVelocity(float deltaTime)
{
	const float displacement = previousPos.Distance(Vector2(playerCollider.GetPosition().x, playerCollider.GetPosition().y));
	const int dotProd = (playerCollider.GetPosition().x * previousPos.x) + (playerCollider.GetPosition().y * previousPos.y);
	const float displacementAngle = dotProd / (Vector2(playerCollider.GetPosition().x , playerCollider.GetPosition().y).Magnitude() * previousPos.Magnitude());
	
	const int speed = static_cast<int>(displacement / deltaTime);
}

void MovementController::ApplyVelocity()
{
	const Vector2 predPos = playerCollider.GetPosition() + velocity;
	const SDL_FRect predRect = SDL_FRect{ predPos.x, predPos.y, playerCollider.GetRect().w, playerCollider.GetRect().h};

	bool collision = false; 

	for (auto& collider : levelColliders)
	{
		if (&playerCollider == collider) continue;

		// Using an if statement so that the value doesn't change after each iteration of the loop
		if(SDL_HasIntersectionF(&predRect, &collider->GetRect())) collision = true;

		// Allows you to stick to walls (definitely a feature)
		grounded = collision;

		if (collision) return;
	}


	playerCollider.SetPosition(playerCollider.GetPosition() + velocity);
}


void MovementController::Move(float deltaTime)
{
	if (controller.GetMoveInputs()[0]) Jump();
	if (controller.GetMoveInputs()[1]) Crouch();

	if(!canMove) return;

	if((controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3]) && currentMoveState != EMovementState::CrouchIdle) currentMoveState = EMovementState::Moving;

	const bool left = controller.GetMoveInputs()[2];
	const bool right = controller.GetMoveInputs()[3];
	direction.x = left ? -1 : (right ? 1 : 0);


	velocity.x += moveSpeed * direction.x;
}

void MovementController::Jump()
{
	if(!grounded) return;

	velocity.y -= jumpForce;
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
