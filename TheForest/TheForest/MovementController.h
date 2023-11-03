#pragma once

#include "Physics.h"

class MovementController:Physics
{
public:
    MovementController();
    void Update(double deltaTime);

    enum EMovementState; 
    Vector2 position = Vector2();

private:
    void CalculateVelocity(double deltaTime);
    void Jump();
    void Slide();
    void Crouch();
    void Move();

    short currentMoveState;
    const float moveSpeed = 5;

    const float mass = 100;
    const float jumpForce = 100;
    const float slideSpeed = 10;

    Vector2 direction = Vector2();
    Vector2 previousPos = Vector2();
    Vector2 velocity = Vector2();
};