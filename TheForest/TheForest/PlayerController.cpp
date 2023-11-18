#include "Controllers.h"

void PlayerController::Update()
{
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

	
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		CalcMousePosition(e);
	}
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

void PlayerController::CalcMousePosition(SDL_Event& e)
{
	mousePos = Vector2(e.motion.x, e.motion.y);
}
