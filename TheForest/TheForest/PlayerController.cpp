#include "PlayerController.h"
#include <SDL.h>



PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
	ReadInputs();
}

bool* PlayerController::GetMoveInputs()
{
	return moveInputs;
}

bool PlayerController::IsLMB() const
{
	return lmb;
}

bool PlayerController::IsRMB() const
{
	return rmb;
}

void PlayerController::ClearInputs()
{
	lmb = false;
	rmb = false;

	for (bool& moveInput : moveInputs) moveInput = false;
}

void PlayerController::ReadInputs()
{
	ClearInputs();
	
	SDL_Event e;

	///input detection
	while (SDL_PollEvent(&e))
	{
		switch (e.key.keysym.scancode)
		{
		//// Movement
		case SDL_SCANCODE_W:
			// UP / JUMP
			moveInputs[0] = true;
			break;

		case SDL_SCANCODE_S:
			// DOWN / CROUCH
			moveInputs[1] = true;
			break;

		case SDL_SCANCODE_A:
			// LEFT
			moveInputs[2] = true;
			break;

		case SDL_SCANCODE_D:
			// RIGHT
			moveInputs[3] = true;
			break;

		// Jump and Crouch are able to be inputted using W and S since the game is 2D. 
		case SDL_SCANCODE_SPACE:
			// JUMP / UP
			moveInputs[0] = true;
			break;

		case SDL_SCANCODE_LCTRL:
			// CROUCH / DOWN
			moveInputs[1] = true;
			break;

		//// Actions			
		case SDL_BUTTON_LEFT:
			lmb = true;
			break;

		case SDL_BUTTON_RIGHT:
			rmb = true;
			break;


		default:
			ClearInputs();
			break;
		} 
	}
}
