#pragma once

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Update();
	void Draw();

private:
	void StartGame();
	
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	SDL_Window* window;
	SDL_Renderer* renderer;
};