#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded();

    virtual const Vector2& GetVelocity() const { return velocity; }
    
    void AddForce(Vector2 direction, int force);
    void AddForce(int x, int y, int force);

private:
    bool gravityOn = true;

protected:
    Vector2 velocity;
    Vector2 airFriction{2, 2};

    // Lowered = whether the gravity should be floatier
    void ApplyGravity(bool lowered = false, bool accelerated = false);
    void SetGravity(const bool on) { gravityOn = on; }
    static constexpr int gravity = 10;
    int currentGravity;
    
    void SetGrounded(bool isGrounded) { grounded = isGrounded; }
    bool grounded = false;
};

