#pragma once

#include <iostream>
#include <vector>
#include "Vector2.h"
#include "SDL.h"

#define print(x) { std::cout<< x << std::endl; }

class Input
{
public:
    Input(SDL_Scancode button);
    Input(SDL_Scancode button1, SDL_Scancode button2);

    void SetPressed(bool pressed) { isDown = pressed; }

    bool IsKeyDown() const { return isDown; }

    SDL_Scancode GetPrimaryKey() const;
    SDL_Scancode GetSecondaryKey() const;

private:
    bool isDown;

    SDL_Scancode primaryKey;
    SDL_Scancode secondaryKey;
};





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
	
    std::vector<Input> inputs = std::vector<Input>();

	// Up .. Down .. Left .. Right
	bool moveInputs[4];

	void HandleInputs();
	void ReadInputs(SDL_Event& e);
};





/* ------------------ Movement ------------------ */
#include "Physics.h"

class MovementController : public Physics
{
public:
    MovementController(PlayerController& ctrl, Vector2& plyrPos);
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
	
    EMovementState currentMoveState = EMovementState::Idle;
    float moveSpeed = 5;

    const float mass = 100;
    float jumpForce = 100;
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
