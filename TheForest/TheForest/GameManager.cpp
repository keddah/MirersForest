#include "GameManager.h"

GameManager::GameManager()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow(
		"Mirer's Forest",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	GameRenderer::SetRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	if (!GameRenderer::GetRenderer()) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderSetVSync(GameRenderer::GetRenderer(), 1);
	
	running = true;
}

GameManager::~GameManager()
{
	manager;
	
	SDL_DestroyRenderer(GameRenderer::GetRenderer());
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager::Update()
{
	Time::Update();
	const float deltaTime = Time::GetDeltaTime();

	manager.Update(deltaTime);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) running = false;
	}

	if(running) return;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager::Draw()
{
	SDL_SetRenderDrawColor(GameRenderer::GetRenderer(), 125, 0, 125, 255);
	SDL_RenderFillRect(GameRenderer::GetRenderer(), nullptr);

	SDL_RenderClear(GameRenderer::GetRenderer());
	manager.Draw();
	SDL_RenderPresent(GameRenderer::GetRenderer());
}

bool GameManager::IsRunning()
{
	return running;
}