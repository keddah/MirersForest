/**************************************************************************************************************
* Vector2 - Code
*
* The code file for the Vector2 class. Gives functionality to operators like   += ... *=    as well as
* Creates functions that are used to compare the distances of the 2 Vector2's.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float X, float Y)
{
	x = X;
	y = Y;
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return { x,y };
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return { x,y };
}

Vector2 Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return { x,y };
}

Vector2 Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;

	return { x,y };
}

// Unused 
bool Vector2::Compare(const Vector2& other, const float tolerance) const
{
	const bool equal_x = (x >= static_cast<float>(other.x) + tolerance || static_cast<float>(other.x) >= x + tolerance) ||
		x >= static_cast<float>(other.x) - tolerance || static_cast<float>(other.x) >= x - tolerance;

	const bool equal_y = (y >= static_cast<float>(other.y) + tolerance || static_cast<float>(other.y) >= y + tolerance) ||
		y >= static_cast<float>(other.y) - tolerance || static_cast<float>(other.y) >= y - tolerance;

	return  equal_x && equal_y;
}

float Vector2::Magnitude() const
{
	return sqrt((x * x) + (y * y));
}

// Used this to check collisions since it was more reliable
float Vector2::Distance(const Vector2& other) const
{
	const int difference_x = x - other.x;
	const int difference_y = y - other.y;

	// The magnitude of the difference = the distance between the 2 points
	const float distance = Vector2(difference_x, difference_y).Magnitude();
	return distance;
}