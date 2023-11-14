#pragma once

#include <iostream>
#include "Vector2.h"

#define print(x) { std::cout<< x << std::endl; }

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update();
	
	bool* GetMoveInputs();
	Vector2& GetMousePosition() { return mousePos; }
	bool IsLMB() const;
	bool IsRMB() const;

	
private:
	bool lmb;
	bool rmb;
	Vector2 mousePos;

	void ClearInputs();
	
	// Up .. Down .. Left .. Right
	bool moveInputs[4];
	void ReadInputs();
};





/* ------------------ Movement ------------------ */
#include "Physics.h"

class MovementController : public Physics
{
public:
    MovementController(PlayerController& ctrl, Vector2& plyrPos);
    ~MovementController() = default;

    void Update(float deltaTime);

    enum EMovementState
    {
        Idle,
        Moving,
        CrouchIdle,
    	CrouchMoving,
        Sliding
    };

	void ResetSpriteSize(const Vector2& newSize);

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
    int moveSpeed = 1;

    const float mass = 100;
    int jumpForce = 100;
    int slideSpeed = 10;

    Vector2 direction = Vector2(0, 1);

    // Used to calculate velocity
    Vector2 previousPos = Vector2();
	Vector2 spriteSize;
};





/* ------------------ Weapon ------------------ */
#include "Vector2.h"
#include <vector>

class WeaponController
{
public:
    WeaponController(PlayerController& ctrl, Vector2& plyrPos);
    ~WeaponController();

    void Update(float deltaTime);


private:
    PlayerController& controller;

    enum WeaponType
    {
        Normal,
        CloseRange,
        Sniper,
        Melee
    };

    short currentWeapon = Normal;

    bool primaryShot = false;
    bool secondaryShot = false;

    Vector2& playerPosition;
    // Projectile spawn position
    Vector2 spawnPos = Vector2();

    // std::vector<> projectiles = ;
};
