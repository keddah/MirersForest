#include "Physics.h"

#include "CustomTimer.h"

// Reset = whether or not to reset the air time
void Physics::AddForce(const Vector2 direction, const float force, bool reset)
{
	velocity += Vector2(direction.x * force, direction.y * force);

	constexpr short timeSteps = 100;
	const Vector2 projectedPos = velocity + position * timeSteps;
	
	const float percentage = velocity.Magnitude() / projectedPos.Magnitude();
	velocity -= Vector2(1,1) * percentage;
	
	// Limiting the velocity
	if(velocity.x > maxSpeed) velocity.x = maxSpeed;
	if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;

	if(velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
	if(velocity.y < -maxFallSpeed) velocity.y = -maxFallSpeed;

	if(reset) airTime = 0;
}

void Physics::AddForce(const float x, const float y, const float force, bool reset)
{
	velocity += Vector2(x * force, y * force);

	constexpr short timeSteps = 100;
	Vector2 projectedPos = velocity + position * timeSteps;
	
	const float percentage = velocity.Magnitude() / projectedPos.Magnitude();
	velocity -= Vector2(1,1) * percentage;
	
	// Limiting the velocity
	if(velocity.x > maxSpeed) velocity.x = maxSpeed;
	if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;

	if(velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
	if(velocity.y < -maxFallSpeed) velocity.y = -maxFallSpeed;
	
	if(reset) airTime = 0;
}

void Physics::ApplyGravity(bool isCharacter, bool lowered, bool accelerated)
{
	if(!gravityOn || grounded)
	{
		// Reset air time when the player lands
		if(grounded) airTime = 0;
		return;
	}

	if(isCharacter)
	{
		// Add to the air time...
		airTime += Time::GetDeltaTime();

		// Depending on how long the thing has been in the air ... apply gravity multipliers.

		// Use lighter gravity if the air time is longer than x seconds.
		if(airTime < .4f) currentGravity = Gravity * at_gravMultiplierLow;

		// Use normal gravity if the air time is longer than x seconds.
		else currentGravity = Gravity;

		// Use heavier gravity if the airtime is longer than x seconds.
		if(airTime > .8) currentGravity  = Gravity * at_gravMultiplierHigh;
	}
	// If lowered gravity... dampen the gravity.. otherwise .. if accelerated gravity.. strengthen it... otherwise.. normal gravity.
	// (prioritises lowered gravity)
	AddForce(Vector2(0, 1), lowered? currentGravity * .6f : accelerated? currentGravity * 1.4f: currentGravity);
}
