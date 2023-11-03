#pragma once

class MovementController :: Physics
{
public: 
    MovementController();    
    void Update();

    enum EMovementState

private:
    void Jump();
    void Slide();
    void Crouch();
    void Move();

    byte currentMoveState
    const float moveSpeed = 5; 

    const float mass = 100; 
    const float jumpForce = 100; 
    const float slideSpeed = 10;
 

};