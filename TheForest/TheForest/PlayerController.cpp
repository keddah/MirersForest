#include "Controllers.h"
#include "GameSingletons.h"

void PlayerController::Update()
{
	ClearInputs();
	HandleInputs();
}

bool* PlayerController::GetMoveInputs()
{
	return moveInputs;
}

void PlayerController::HandleInputs()
{
	const Uint8* keyState = SDL_GetKeyboardState(0);

	moveInputs[0] = keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_SPACE];
	moveInputs[1] = keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_LCTRL];
	moveInputs[2] = keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT];
	moveInputs[3] = keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT];

	num1 = keyState[SDL_SCANCODE_1];
	num2 = keyState[SDL_SCANCODE_2];
	num3 = keyState[SDL_SCANCODE_3];
	num4 = keyState[SDL_SCANCODE_4];

	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	mousePos.x = mouse_x;
	mousePos.y = mouse_y;
	
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.button == SDL_BUTTON_LEFT) lmb = true;
			if(e.button.button == SDL_BUTTON_RIGHT) rmb = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if(e.button.button == SDL_BUTTON_LEFT) lmb = false;
			if(e.button.button == SDL_BUTTON_RIGHT) rmb = false;
			break;

		case SDL_MOUSEWHEEL:
			wheelUp = e.wheel.y > 0;
			wheelDown = e.wheel.y < 0;
			break;
		
		case SDL_QUIT:
			GameWindow::CloseGame();
			break;

		case SDL_KEYDOWN:
			// Toggle pause down
			if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE || e.key.keysym.scancode == SDL_SCANCODE_P) pauseDown = !pauseDown;
			break;
		}
			
	}
}

void PlayerController::ClearInputs()
{
	wheelUp = false;
	wheelDown = false;

	num1 = false;
	num2 = false;
	num3 = false;
	num4 = false;

	for (bool& moveInput : moveInputs) moveInput = false;
}