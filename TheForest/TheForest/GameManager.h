#pragma once

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "SceneManager.h"
#include "CustomTimer.h"
#include "GameSingletons.h"

#define DEBUGGING 1

#if DEBUGGING == 1
#define print(x){std::cout << (x) << std::endl;}

#elif DEBUGGING == 0
#define print(x)

#endif

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Update();
	void Draw();

	bool IsRunning() const;


private:
	bool running;
	
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	SceneManager manager;
};