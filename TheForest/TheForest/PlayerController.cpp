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
	SDL_Event e;
	SDL_PollEvent(&e);
	ClearInputs();

	if (e.type == SDL_KEYUP)
	{
		ClearInputs();

		for (auto& input : inputs)
		{
			if (e.key.keysym.scancode == input.GetSecondaryKey()) input.SetPressed(false);
			else if (e.key.keysym.scancode == input.GetPrimaryKey()) input.SetPressed(false);
		}
		//print("keyup")
	}

	if (e.type == SDL_KEYDOWN)
	{
		ClearInputs();

		for (auto& input : inputs)
		{
			if (e.key.keysym.scancode == input.GetSecondaryKey()) input.SetPressed(true);
			else if (e.key.keysym.scancode == input.GetPrimaryKey()) input.SetPressed(true);
		}
		//print("keydown")
	}

	ReadInputs(e);
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

void PlayerController::ReadInputs(SDL_Event& e)
{
	///input detection
	mousePos = Vector2(e.motion.x, e.motion.y);

	moveInputs[0] = inputs[0].IsKeyDown();
	moveInputs[1] = inputs[1].IsKeyDown();
	moveInputs[2] = inputs[2].IsKeyDown();
	moveInputs[3] = inputs[3].IsKeyDown();

	moveInputs[0] = inputs[4].IsKeyDown();
	moveInputs[1] = inputs[5].IsKeyDown();

	switch (e.key.keysym.scancode)
	{
		//// Actions			
		case SDL_BUTTON_LEFT:
			lmb = true;
			break;

		case SDL_BUTTON_RIGHT:
			rmb = true;
			break;


		default:
			break;
	} 
}
