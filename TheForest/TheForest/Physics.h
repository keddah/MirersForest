#pragma once

#include "Vector2.h"

class Physics
{
public:
    bool IsGrounded();

    void AddForce(Vector2 direction, int force);
    void AddForce(int x, int y, int force);
    bool grounded;

private:
    const int terminalSpeed = 200;
    bool gravityOn = true;

protected:
    Vector2 velocity;
    
    void ApplyGravity();
    void SetGravity(const bool on) { gravityOn = on; }
    
    static constexpr int gravity = 10;


};

