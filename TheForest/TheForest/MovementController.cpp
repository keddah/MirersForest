#include "MovementController.h"

MovementController::MovementController()
{
}

void MovementController::Update(double deltaTime)
{
	ApplyGravity();
	CalculateVelocity(deltaTime);
}

void MovementController::CalculateVelocity(double deltaTime)
{
	const float Displacement = previousPos.Distance(Vector2(position.x, position.y));
	const float dotProd = (position.x * previousPos.x) + (position.y * previousPos.y);
	const float displacementAngle = dotProd / position.Magnitude() * previousPos.Magnitude();

	const float speed = Displacement / deltaTime;

	velocity = direction * speed;
}

void MovementController::Jump()
{
	velocity = AddForce(velocity + Vector2(0, 2), jumpForce);
}
