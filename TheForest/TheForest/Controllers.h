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

	const Vector2& GetMousePosition() const { return mousePos; }
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
