#pragma once

#include "Physics.h"
#include "PlayerController.h" 

class MovementController:Physics
{
public:
    MovementController(PlayerController& ctrl, Vector2& plyrPos);
    ~MovementController() {}
    
    void Update(float deltaTime);

    //Vector2& GetPosition() {}
    
    enum EMovementState
    {
        Idle,
        Moving,
        Crouching,
        Sliding
    };
    
private:
    void CalculateVelocity(float deltaTime);
    void CalculateDirection();
    
    void Jump();
    void Slide();
    void Crouch();
    void Uncrouch();
    void Move();

    PlayerController& controller;
    Vector2& playerPosition;

    bool canMove = true;
    
    short currentMoveState = Idle;
    const int moveSpeed = 5;

    const float mass = 100;
    const int jumpForce = 100;
    const int slideSpeed = 10;

    Vector2 direction = Vector2();

    // Used to calculate velocity
    Vector2 previousPos = Vector2();
    Vector2 velocity = Vector2();
};
