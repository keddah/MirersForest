#include "Controllers.h"


PlayerController::PlayerController()
{
	Input up = Input(SDL_SCANCODE_W, SDL_SCANCODE_UP);
	Input down = Input(SDL_SCANCODE_S, SDL_SCANCODE_DOWN);
	Input left = Input(SDL_SCANCODE_A, SDL_SCANCODE_LEFT);
	Input right = Input(SDL_SCANCODE_D, SDL_SCANCODE_RIGHT);

	Input space = Input(SDL_SCANCODE_SPACE);
	Input ctrl = Input(SDL_SCANCODE_LCTRL);

	
	inputs = { up, down, left, right, space, ctrl };
}

PlayerController::~PlayerController()
{
}

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
	inputs[0].SetPressed(keyState[SDL_SCANCODE_W]);
	inputs[1].SetPressed(keyState[SDL_SCANCODE_S]);
	inputs[2].SetPressed(keyState[SDL_SCANCODE_A]);
	inputs[3].SetPressed(keyState[SDL_SCANCODE_D]);
	inputs[4].SetPressed(keyState[SDL_SCANCODE_SPACE]);
	inputs[5].SetPressed(keyState[SDL_SCANCODE_LCTRL]);

	moveInputs[0] = inputs[0].IsKeyDown();
	moveInputs[1] = inputs[1].IsKeyDown();
	moveInputs[2] = inputs[2].IsKeyDown();
	moveInputs[3] = inputs[3].IsKeyDown();

	moveInputs[0] = inputs[4].IsKeyDown();
	moveInputs[1] = inputs[5].IsKeyDown();
	
	SDL_Event e;
	while(SDL_PollEvent(&e)) CalcMousePosition(e);
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
