/**************************************************************************************************************
* Game Manager - Code
*
* The code file for the Game manager class. Initiates SDL, creates a window and a renderer.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "GameManager.h"


// Initialise SDL in this constructor
GameManager::GameManager()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	GameWindow::SetWindow
	(
		SDL_CreateWindow
		(
		"Mirer's Forest",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
		)
	);
	if (!GameWindow::GetWindow())
	{
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	GameWindow::SetWindowSize(screenWidth, screenHeight);

	GameWindow::SetRenderer(SDL_CreateRenderer(GameWindow::GetWindow(), -1, SDL_RENDERER_ACCELERATED));
	if (!GameWindow::GetRenderer())
	{
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderSetVSync(GameWindow::GetRenderer(), 1);

	pSession = std::make_unique<GameSession>();
	running = true;
}


void GameManager::Draw() const
{
	// Clear the screen before rendering something new
	SDL_RenderClear(GameWindow::GetRenderer());

	// Render everything that needs to be rendered in the current session
	pSession->Draw();

	// Actually display the new things
	SDL_RenderPresent(GameWindow::GetRenderer());
}