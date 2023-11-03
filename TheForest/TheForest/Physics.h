#pragma once

class Physics
{
public:
    bool IsGrounded();
    void AddForce(float force);

protected:
    void ApplyGravity();

    static constexpr float Gravity = 10;

    bool grounded;

};

