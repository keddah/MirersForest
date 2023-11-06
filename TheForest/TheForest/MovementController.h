#pragma once

#include "Physics.h"
#include "Player.h"

class MovementController:Physics
{
public:
    MovementController(Player*& plyr);
    void Update(double deltaTime);

    Vector2& GetPosition();
    
    enum EMovementState
    {
        Idle,
        Moving,
        Crouching,
        Sliding
    };
    
private:
    void CalculateVelocity(double deltaTime);
    void CalculateDirection();
    
    void Jump();
    void Slide();
    void Crouch();
    void Move();

    Player* player;

    Vector2 position = Vector2();

    bool canMove = true;
    
    short currentMoveState = Idle;
    const float moveSpeed = 5;

    const float mass = 100;
    const float jumpForce = 100;
    const float slideSpeed = 10;

    Vector2 direction = Vector2();
    Vector2 previousPos = Vector2();
    Vector2 velocity = Vector2();
};
