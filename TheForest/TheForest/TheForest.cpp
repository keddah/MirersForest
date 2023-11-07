// TheForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "GameManager.h"

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

