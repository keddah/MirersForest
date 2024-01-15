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
	~GameManager()
	{
		running = false;
		GameWindow::CloseGame();
	}

	// These get called in a while loop in the main function
	void Update() const { pSession->Update(Time::GetDeltaTime()); }
	void FixedUpdate() const { pSession->FixedUpdate(Time::GetDeltaTime()); }
	void Draw() const;

	bool IsRunning() const { return running; }


private:
	bool running;
	std::unique_ptr<GameSession> pSession;
	
	static constexpr int screenWidth = 1920;
	static constexpr int screenHeight = 1080;

	SDL_Renderer* renderer;
};