#include "GameManager.h"

GameManager::GameManager()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		print("could not initialize SDL2!")
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
		print("could not initialise window!")
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	GameWindow::SetRenderer(SDL_CreateRenderer(GameWindow::GetWindow(), -1, SDL_RENDERER_ACCELERATED));
	if (!GameWindow::GetRenderer())
	{
		print("could not initialise window!")
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderSetVSync(GameWindow::GetRenderer(), 1);

	running = true;
	manager = new SceneManager();
}

GameManager::~GameManager()
{
	delete manager;
	SDL_DestroyRenderer(GameWindow::GetRenderer());
	SDL_DestroyWindow(GameWindow::GetWindow());
	SDL_Quit();
}

void GameManager::Update()
{
	const float deltaTime = Time::GetDeltaTime();

	manager->Update(deltaTime);
}

void GameManager::Draw()
{
	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), 0, 15, 10, 255);
	SDL_RenderFillRect(GameWindow::GetRenderer(), nullptr);

	SDL_RenderClear(GameWindow::GetRenderer());
	manager->Draw();
	SDL_RenderPresent(GameWindow::GetRenderer());
}

bool GameManager::IsRunning() const
{
	return running;
}
