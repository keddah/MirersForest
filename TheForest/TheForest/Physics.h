#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded() { return grounded; }

    virtual const Vector2& GetVelocity() const { return velocity; }
    
    void AddForce(Vector2 direction, float force);
    void AddForce(float x, float y, float force);

private:
    bool gravityOn = true;
    float airTime;

protected:
    Vector2 velocity;
    Vector2 pos;

    float GetAirTime() { return airTime; }
    
    float at_gravMultiplierHigh = 10;
    float at_gravMultiplierLow = .15f;
    float maxSpeed;
    float maxFallSpeed;

    // Lowered = whether the gravity should be floatier
    void ApplyGravity(bool lowered = false, bool accelerated = false);
    void SetGravity(const bool on) { gravityOn = on; }
    static constexpr float Gravity = 9.81f;
    float currentGravity = Gravity;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = false;
};

