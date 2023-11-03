#pragma once

class Physics
{
public:
    bool IsGrounded();
    void AddForce(float force);
    void SetGravity(bool on);

private:
    bool gravityOn = true;

protected:
    void ApplyGravity();

    static constexpr float Gravity = 10;

    bool grounded;

};

