/**************************************************************************************************************
* Physics - Header
*
* The header file for the Player class. This class won't be directly instantiated as it will be the parent class to classes that need gravity.
* This class provides functions and variables that will allow objects that inherit this class to have access to physics properties.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once

#include "Vector2.h"
#include <iostream>

class Physics
{
public:
    virtual void SetGravity(const bool on) { gravityOn = on; }
    virtual Vector2 GetVelocity() const { return velocity; }

private:
    bool gravityOn = true;
    float airTime;

protected:
    Vector2 position;
    Vector2 velocity;

    void AddForce(Vector2 direction, float force, bool reset = false);
    void AddForce(float x, float y, float force, bool reset = false);
    void SetVelocity(float x = 0, float y = 0) { velocity = {x, y}; }
    void SetVelocity(const Vector2 newValue) { velocity = newValue; }
    
    float decelerationRate = 175;
    float drag = 10;

    float GetAirTime() const { return airTime; }

    // The gravity multiplier to be applied when the player has just gone into the air
    const float minLowMultiplier = .15f;
    float lowMultiplier = minLowMultiplier;
    
    float gravMultiplier = 1;
    float maxSpeed = 20;
    float maxFallSpeed = 50;

    // Lowered = whether the gravity should be floatier - Accelerated = the opposite
    void ApplyGravity(bool isCharacter = false, bool lowered = false, bool accelerated = false);
    static constexpr float Gravity = 16;
    float currentGravity = Gravity;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = false;
};

