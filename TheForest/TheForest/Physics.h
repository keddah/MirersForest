#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded();

    virtual const Vector2& GetVelocity() const { return velocity; }
    
    void AddForce(Vector2 direction, float force);
    void AddForce(float x, float y, float force);

private:
    const float terminalSpeed = 200;
    bool gravityOn = true;

protected:
    Vector2 velocity;
    
    void ApplyGravity();
    void SetGravity(const bool on) { gravityOn = on; }
    static constexpr float gravity = 9.81;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = true;
};

