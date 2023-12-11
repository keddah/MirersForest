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