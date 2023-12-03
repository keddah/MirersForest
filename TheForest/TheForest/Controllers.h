#pragma once

#include <iostream>
#include "SDL.h"
#include "Vector2.h"


#define print(x) { std::cout<< x << std::endl; }

class PlayerController
{
public:
	PlayerController() = default;
	~PlayerController() = default;

	void Update();
	
	bool* GetMoveInputs();

	Vector2& GetMousePosition() { return mousePos; }
	bool IsLMB() const { return lmb; }
	bool IsRMB() const { return rmb; }
	
	bool JumpBtnDown() const { return moveInputs[0]; } 
	bool CrouchBtnDown() const { return moveInputs[1]; } 
	bool IsLeft() const { return moveInputs[2]; }
	bool IsRight() const { return moveInputs[3]; }

	
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





/* ------------------ Weapon ------------------ */

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
