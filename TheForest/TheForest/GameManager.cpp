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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	SDL_RenderSetVSync(renderer, 1);
	
	manager = new SceneManager();
	running = true;
}

GameManager::~GameManager()
{
	// SDL_DestroyTexture(character);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager::Update()
{
	Time::Update();
	const float deltaTime = Time::GetDeltaTime();

	manager->Update(deltaTime);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) running = false;
	}


	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, nullptr);

	manager->Draw();
	/*
	SDL_Rect source{ 0, 0, 16, 16 };
	SDL_Rect dest{ x, 0, 50, 50 };
	SDL_RenderCopy(renderer, character, nullptr, &dest);
	*/


	SDL_RenderPresent(renderer);
}

bool GameManager::IsRunning()
{
	return running;
}