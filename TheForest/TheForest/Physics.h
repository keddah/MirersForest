#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded();
    Vector2 AddForce(Vector2 Direction, float force);
    Vector2 AddForce(int x, int y, float force);
    void SetGravity(bool on);

private:
    bool gravityOn = true;

protected:
    void ApplyGravity();

    static constexpr float Gravity = 10;

    bool grounded;

};

