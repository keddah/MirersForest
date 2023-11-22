#pragma once

#include <iostream>
#include "Vector2.h"
#include <vector>
#include "SDL.h"
#include "Collider.h"


#define print(x) { std::cout<< x << std::endl; }

class PlayerController
{
public:
	PlayerController() = default;
	~PlayerController() = default;

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

	void HandleInputs();
	void CalcMousePosition(SDL_Event& e);
};





/* ------------------ Movement ------------------ */
#include "Physics.h"

class MovementController : public Physics
{
public:
    MovementController(PlayerController& ctrl, Collision& playerCollider, const std::vector<Collision*>& colliders);
    ~MovementController() = default;

    void Update(float deltaTime);

    enum class EMovementState
    {
        Idle,
        Moving,
        CrouchIdle,
    	CrouchMoving,
        Sliding
    };

	void ResetSpriteSize(const Vector2& newSize);
	// void BlockingCollisions(const std::tuple<bool, Collision::EObstructionDirection>& obstruction);
	void BlockingCollisions();

private:
    void CalculateVelocity(float deltaTime);
    void CalculateDirection();

    void Move(float deltaTime);
    void Jump();
    void Slide();
    void Crouch();
    void Uncrouch();

    const std::vector<Collision*>& levelColliders;
    Collision& playerCollider;
    PlayerController& controller;

	bool& obstructed = playerCollider.IsObstructed();
	
    bool canMove = true;
	
    EMovementState currentMoveState = EMovementState::Idle;
    float moveSpeed = 5;

    const float mass = 1000;
    float jumpForce = -25;
    float slideSpeed = 10;

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
