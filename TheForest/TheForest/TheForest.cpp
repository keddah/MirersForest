// TheForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "GameManager.h"

// Initially set values.
float Time::deltaTime = 0;
high_resolution_clock::time_point Time::lastFrameTime = high_resolution_clock::now();

SDL_Renderer* GameWindow::renderer = nullptr;
SDL_Window* GameWindow::window = nullptr;

int main()
{
	GameManager game;
	
	while (game.IsRunning())
	{
		Time::Update();
		game.Update();
		game.Draw();
		Time::SetLastFrameTime(high_resolution_clock::now());
	}

	SDL_DestroyWindow(GameWindow::GetWindow());
	SDL_Quit();
	
	return 0;
}

