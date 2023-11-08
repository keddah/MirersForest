// TheForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "GameManager.h"

// Initially set values.
float Time::deltaTime = 0;
high_resolution_clock::time_point Time::lastFrameTime = high_resolution_clock::now();
SDL_Renderer* GameRenderer::renderer = nullptr;

int main()
{
	GameManager game;
	
	while (game.IsRunning())
	{
		game.Update();
		game.Draw();
	}

	return 0;
}

