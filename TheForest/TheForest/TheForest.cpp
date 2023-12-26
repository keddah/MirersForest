/**************************************************************************************************************
* The Forest - Code
*
* This file contains the 'main' function. Program execution begins and ends there. This is where the game loops are created and the singleton values are set
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/
#include "GameManager.h"

// Initially set values for the time.
float Time::deltaTime = 0;
float Time::elapsedGameTime = 0;
float Time::currentTime = 0;
float Time::newTime = 0;

// Initially set values for the window.
SDL_Renderer* GameWindow::renderer = nullptr;
SDL_Window* GameWindow::window = nullptr;

int GameWindow::windowWidth = 0;
int GameWindow::windowHeight = 0;

int main()
{
	// Create an instance of the game
	const GameManager game;

	// Using this as the starting point of the delta time
	Time::SetCurrentTime(Time::GetElapsedTime());

	// Used for fixed update;
	float tickTimer = 0;

	while (game.IsRunning())
	{
		// The time that has to elapse in order for fixed update to tick.
		constexpr float timeStep = .0125f;
		
		Time::Update();

		game.Update();
		
		// When the timer elapses... do the fixed update.
		tickTimer += Time::GetDeltaTime();
		while(tickTimer > timeStep)
		{
			game.FixedUpdate();
			tickTimer = 0;
		}
		
		game.Draw();
		Time::SetLastFrameTime();
	}

	SDL_DestroyWindow(GameWindow::GetWindow());
	SDL_Quit();
	
	return 0;
}

