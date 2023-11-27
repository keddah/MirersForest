/**************************************************************************************************************
* Vector2 - Header
*
* The header file for the Vector2 class. Allows math operators to be applied to Vectors accordingly.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(int X, int Y);

	int x, y;

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const int multiplier);
	Vector2 operator/=(const int divider);

	Vector2 operator+(const Vector2& other) const
	{
		return {x + other.x, y + other.y};
	}

	Vector2 operator-(const Vector2& other) const
	{
		return {x + other.x, y + other.y};
	}

	Vector2 operator*(const int multiplier) const
	{
		
		return {x * multiplier, y * multiplier};
	}
	Vector2 operator/(const int divider) const
	{
		return {x / divider, y / divider};
	}
	
	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return x != other.x || y != other.y;
	}

	bool Compare(const Vector2& other, float tolerance) const;


	float Magnitude() const;

	float Distance(const Vector2& other) const;
};