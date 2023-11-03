#include "PlayerController.h"
#include <SDL.h>



PlayerController::PlayerController()
{
}

void PlayerController::Update()
{
	ReadInputs();
}

bool* PlayerController::GetInputs()
{
	return moveInputs;
}

void PlayerController::ReadInputs()
{
	for (int i = 0; i < 4; i++) moveInputs[i] = false;

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		///input detection
		switch (e.key.keysym.scancode)
		{
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

		default:
			for (int i = 0; i < 4; i++) moveInputs[i] = false;
			break;
		} 
	}
}
