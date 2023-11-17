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

	moveInputs[0] = keyState[SDL_SCANCODE_W];
	moveInputs[1] = keyState[SDL_SCANCODE_S];
	moveInputs[2] = keyState[SDL_SCANCODE_A];
	moveInputs[3] = keyState[SDL_SCANCODE_D];

	moveInputs[0] = keyState[SDL_SCANCODE_SPACE];
	moveInputs[1] = keyState[SDL_SCANCODE_LCTRL];
	
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
