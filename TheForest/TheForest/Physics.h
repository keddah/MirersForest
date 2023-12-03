#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded() const { return grounded; }

    virtual const Vector2& GetVelocity() const { return velocity; }
    
    void AddForce(Vector2 direction, float force);
    void AddForce(float x, float y, float force);

private:
    bool gravityOn = true;
    float airTime;

protected:
    Vector2 position;
    Vector2 velocity;
    
    const float decelerationRate = 175;
    float drag = 10;


    float GetAirTime() const { return airTime; }
    
    float at_gravMultiplierHigh = 10;
    float at_gravMultiplierLow = .15f;
    float maxSpeed = 20;
    float maxFallSpeed = 50;

    // Lowered = whether the gravity should be floatier - Accelerated = the opposite
    void ApplyGravity(bool isCharacter = false, bool lowered = false, bool accelerated = false);
    void SetGravity(const bool on) { gravityOn = on; }
    static constexpr float Gravity = 9.81f;
    float currentGravity = Gravity;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = false;
};

