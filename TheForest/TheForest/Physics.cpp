/**************************************************************************************************************
* Physics - Code
*
* The code file for the Physics class. Responsible for giving functionality to the Add force function and Gravity function.
* These are the 2 main functions of the physics class.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Physics.h"

#include "CustomTimer.h"

// Reset = whether or not to reset the air time
void Physics::AddForce(const Vector2 direction, const float force, bool reset)
{
	// Add the force
	velocity += Vector2(direction.x * force, direction.y * force);

	// Predict the path of the object
	constexpr short timeSteps = 100;
	const Vector2 projectedPos = velocity + position * timeSteps;

	// Drag
	const float percentage = velocity.Magnitude() / projectedPos.Magnitude();
	velocity -= Vector2(1,1) * (percentage < .025f? 0 : percentage);
	
	// Limiting the velocity
	if(velocity.x > maxSpeed) velocity.x = maxSpeed;
	if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;

	if(velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
	if(velocity.y < -maxFallSpeed) velocity.y = -maxFallSpeed;

	if(reset) airTime = 0;
}

void Physics::AddForce(const float x, const float y, const float force, bool reset)
{
	// Add the force
	velocity += Vector2(x * force, y * force);

	// Predict the path of the object
	constexpr short timeSteps = 100;
	const Vector2 projectedPos = velocity + position * timeSteps;

	// Drag
	const float percentage = velocity.Magnitude() / projectedPos.Magnitude();
	velocity -= Vector2(1,1) * (percentage < .1f? 0 : percentage);
	
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
		if(airTime < .18f)
		{
			lowMultiplier = minLowMultiplier;
			currentGravity = Gravity * lowMultiplier;
		}

		// Use normal gravity if the air time is longer than x seconds.
		else
		{
			// Slowly add increase the gravity until the multiplier is 1
			lowMultiplier += .005f;
			if(lowMultiplier > 1) lowMultiplier = 1;
			
			currentGravity = Gravity * lowMultiplier;
		}
	}
	// If lowered gravity... dampen the gravity.. otherwise .. if accelerated gravity.. strengthen it... otherwise.. normal gravity.
	// (prioritises lowered gravity)
	AddForce(Vector2(0, 1), (lowered? currentGravity * .6f : accelerated? currentGravity * 1.4f: currentGravity) * gravMultiplier);
}
