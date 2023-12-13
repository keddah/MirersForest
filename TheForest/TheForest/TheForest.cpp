// TheForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "GameManager.h"

// Initially set values for the time.
float Time::deltaTime = 0;
float Time::elapsedGameTime = 0;
float Time::currentTime = 0;
float Time::newTime = 0;

// Initially set values for the window.
SDL_Renderer* GameWindow::renderer = nullptr;
SDL_Window* GameWindow::window = nullptr;
Vector2 GameWindow::windowSize = {};

int main()
{
	GameManager game;

	Time::SetCurrentTime(Time::GetElapsedTime());

	float tickTimer = 0;
	const float timeStep = .001f;
	
	while (game.IsRunning())
	{
		Time::Update();
		game.Update();
		game.Draw();
		Time::SetLastFrameTime();

		tickTimer += Time::GetDeltaTime();
		while(tickTimer > timeStep)
		{
			game.FixedUpdate();
			tickTimer = 0;
		}
		
	}

	SDL_DestroyWindow(GameWindow::GetWindow());
	SDL_Quit();
	
	return 0;
}

