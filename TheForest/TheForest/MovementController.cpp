#include "Controllers.h"

MovementController::MovementController(PlayerController& ctrl, Collision& _playerCollider, const std::vector<Collision*>& colliders) :
controller(ctrl), playerCollider(_playerCollider), levelColliders(colliders)
{
}


void MovementController::Update(float deltaTime)
{
	// Reset the velocity at the start of each frame so that it isn't infinitely increased.
	velocity = Vector2();

	if(playerCollider.GetPosition().y <= 1080 - spriteSize.y) ApplyGravity();
	//CalculateDirection();
	BlockingCollisions();
	Move(deltaTime);

	 //ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
	
	// slightly reduce gravity if holding down the jump button // slightly increase gravity when holding crouch
	Vector2 predPos = playerCollider.GetPosition() + velocity;


	SDL_FRect predRect = SDL_FRect{ predPos.x, predPos.y, playerCollider.GetRect().w, playerCollider.GetRect().h };

	for (auto& collider : levelColliders)
	{
		if (&playerCollider == collider) {

			continue;
		}
		if (SDL_HasIntersectionF(&predRect, &collider->GetRect()))
		{
			return;
			canMove = true;
			direction = Vector2(-1, direction.y);
			direction = Vector2(1, direction.y);
		}
		else canMove = false;
	}


	print(velocity.x)

	playerCollider.SetPosition(playerCollider.GetPosition() + velocity);
	// CorrectCollisions();
	// Since the position is the top left of the image... have to get the bottom.
	
	//if(playerCollider.GetPosition().y + velocity.y > 1080) playerCollider.SetPosition(playerCollider.GetPosition().x, 0);
	//else if(playerCollider.GetPosition().y > 1080) playerCollider.SetPosition(playerCollider.GetPosition().x, 0);
	//
	//else if(playerCollider.GetPosition().x > 1920) playerCollider.SetPosition(0, playerCollider.GetPosition().y);
	//else if(playerCollider.GetPosition().x < 0) playerCollider.SetPosition(1900, playerCollider.GetPosition().y);
	//

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

void MovementController::CalculateDirection()
{
	direction = Vector2();
	
	// There are only 4 movement inputs
	Vector2 predPos = playerCollider.GetPosition() + velocity;

	for(int i = 0; i < 4; i++)
	{
		// 0 = up, 1 = down, 2 = left, 3 = right
		const bool up = controller.GetMoveInputs()[0];
		const bool down = controller.GetMoveInputs()[1];
		const bool left = controller.GetMoveInputs()[2];
		const bool right = controller.GetMoveInputs()[3];

		if(up) Jump();
		if(down) Crouch();

		SDL_FRect rect = playerCollider.GetRect();
		const float newX = rect.x + velocity.x;
		const float newY = rect.y + velocity.y;

		for (auto& collider : levelColliders)
		{
			SDL_FRect predRect = SDL_FRect{ predPos.x, predPos.y, playerCollider.GetRect().w, playerCollider.GetRect().h };
			if (!SDL_HasIntersectionF(&predRect, &collider->GetRect()))
			{
				canMove = true;
				direction = Vector2(-1, direction.y);
				direction = Vector2(1, direction.y);
			}
			else canMove = false;
		}

	}
}


void MovementController::BlockingCollisions()
{
	//for (const auto& collider : levelColliders)
	//{
	//	if (&playerCollider == collider) continue;
	//
	//	playerCollider.Overlapping(*collider);
	//}
}

void MovementController::Move(float deltaTime)
{
	//if(!canMove) return;

	if((controller.GetMoveInputs()[2] || controller.GetMoveInputs()[3]) && currentMoveState != EMovementState::CrouchIdle) currentMoveState = EMovementState::Moving;

	velocity.x += moveSpeed * direction.x;
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
