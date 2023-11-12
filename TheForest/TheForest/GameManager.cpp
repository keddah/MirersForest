#include "GameManager.h"

GameManager::GameManager()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Mirer's Forest",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	GameWindow::SetWindow(window);
	
	if (!GameWindow::GetWindow()) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	GameWindow::SetRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	if (!GameWindow::GetRenderer()) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderSetVSync(GameWindow::GetRenderer(), 1);
	
	running = true;
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(GameWindow::GetRenderer());
	SDL_DestroyWindow(GameWindow::GetWindow());
	SDL_Quit();
}

void GameManager::Update()
{
	const float deltaTime = Time::GetDeltaTime();

	manager.Update(deltaTime);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) running = false;
	}
}

void GameManager::Draw()
{
	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), 125, 0, 125, 255);
	SDL_RenderFillRect(GameWindow::GetRenderer(), nullptr);

	SDL_RenderClear(GameWindow::GetRenderer());
	manager.Draw();
	SDL_RenderPresent(GameWindow::GetRenderer());
}

bool GameManager::IsRunning() const
{
	return running;
}
