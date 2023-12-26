/**************************************************************************************************************
* Game Manager - Header
*
* The header file for the Game manager. This class is used to initiate SDL. The draw and update functions are called from the main function.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once

#include <iostream>


#define SDL_MAIN_HANDLED

#include "CustomTimer.h"
#include "GameSession.h"
#include "GameSingletons.h"

#define print(x){std::cout << (x) << std::endl;}

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Update() const;
	void FixedUpdate() const;
	void Draw() const;

	bool IsRunning() const;


private:
	bool running;
	std::unique_ptr<GameSession> session;
	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
};