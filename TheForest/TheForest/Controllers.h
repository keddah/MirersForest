/**************************************************************************************************************
* Controllers - Header
*
* The header file for the Player controller class. Responsible for providing get functions for the player class so that
* it can read inputs (everything is private). 
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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
	

	// Weapons
	const Vector2& GetMousePosition() const { return mousePos; }
	bool IsLMB() const { return lmb; }
	bool IsRMB() const { return rmb; }

	
	// Movement
	bool* GetMoveInputs();
	bool JumpBtnDown() const { return moveInputs[0]; } 
	bool CrouchBtnDown() const { return moveInputs[1]; } 
	bool IsLeft() const { return moveInputs[2]; }
	bool IsRight() const { return moveInputs[3]; }
	
	bool PauseDown() const { return pauseDown; }
	void ResetPaused() { pauseDown = false; }


	// Weapon Selection
	bool WheelUp() const { return wheelUp; }
	bool WheelDown() const { return wheelDown; }
	
	bool OnePressed() const { return num1; }
	bool TwoPressed() const { return num2; }
	bool ThreePressed() const { return num3; }
	// bool FourPressed() const { return num4; }
	

	
private:
	// Up .. Down .. Left .. Right
	bool moveInputs[4];
	
	bool lmb;
	bool rmb;

	bool num1;
	bool num2;
	bool num3;
	// bool num4;
	
	Vector2 mousePos;
	bool wheelUp;
	bool wheelDown;

	bool pauseDown;
	


	void ClearInputs();
	void HandleInputs();
};
