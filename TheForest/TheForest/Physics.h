#pragma once

#include "Vector2.h"
#include <iostream>

class Physics
{
public:
    bool IsGrounded() const { return grounded; }

    void AddForce(Vector2 direction, float force, bool reset = false);
    void AddForce(float x, float y, float force, bool reset = false);
    virtual void SetGravity(const bool on) { gravityOn = on; }

    virtual Vector2 GetVelocity() const { return velocity; }

private:
    bool gravityOn = true;
    float airTime;

protected:
    Vector2 position;
    Vector2 velocity;

    void SetVelocity(float x = 0, float y = 0) { velocity = {x, y}; }
    void SetVelocity(const Vector2 newValue) { velocity = newValue; }
    
    float decelerationRate = 175;
    float drag = 10;


    float GetAirTime() const { return airTime; }
    
    float at_gravMultiplierHigh = 10;
    float at_gravMultiplierLow = .15f;
    float gravMultiplier = 1;
    float maxSpeed = 20;
    float maxFallSpeed = 50;

    // Lowered = whether the gravity should be floatier - Accelerated = the opposite
    void ApplyGravity(bool isPlayer = false, bool lowered = false, bool accelerated = false);
    static constexpr float Gravity = 9.81f;
    float currentGravity = Gravity;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = false;
};

