/**************************************************************************************************************
* Vector2 - Header
*
* The header file for the Vector2 class. Allows math operators to be applied to Vectors accordingly.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/
#define print(x){std::cout << (x) << std::endl;}

#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float X, float Y);

	float x, y;

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const float multiplier);
	Vector2 operator/=(const float divider);

	Vector2 operator+(const Vector2& other) const
	{
		return {x + other.x, y + other.y};
	}

	Vector2 operator-(const Vector2& other) const
	{
		return {x - other.x, y - other.y};
	}

	Vector2 operator*(const float multiplier) const
	{
		
		return {x * multiplier, y * multiplier};
	}
	Vector2 operator/(const float divider) const
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