/**************************************************************************************************************
* Vector2 - Header
*
* The header file for the Vector2 class. Allows math operators to be applied to Vectors accordingly.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#pragma once

#include <cmath>

class Vector2
{
public:
	Vector2();
	Vector2(float X, float Y);

	float x, y;

	void SetNew(float X, float Y) { x = X; y = Y; }

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const Vector2& other);
	Vector2 operator/=(const Vector2& other);

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 newValue;
		newValue.x = x + other.x;
		newValue.y = y + other.y;
		return newValue;
	}


	Vector2 operator-(const Vector2& other) const
	{
		Vector2 newValue;
		newValue.x = x + other.x;
		newValue.y = y + other.y;
		return newValue;
	}

	Vector2 operator-=(const Vector2& other) const
	{
		Vector2 newValue;
		newValue.x = x + other.x;
		newValue.y = y + other.y;
		return newValue;
	}

	Vector2 operator*(const float multiplier) const
	{
		Vector2 newValue;
		newValue.x *= multiplier;
		newValue.y *= multiplier;
		return newValue;
	}

	Vector2 operator/(const float divider) const
	{
		Vector2 newValue;
		newValue.x /= divider;
		newValue.y /= divider;
		return newValue;
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return x != other.x || y != other.y;
	}

	bool Compare(const Vector2& other, float tolerance = 0) const;


	float Magnitude() const;

	float Distance(const Vector2& other) const;
};