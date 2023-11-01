// TheForest.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>


const int screenWidth = 1920;
const int screenHeight = 1080;


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}


	// Make game objects here


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, NULL);

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
	

	bool quit = false;
	while (!quit)
	{
		SDL_Event e;
	
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT) quit = true;
			if (e.key.keysym.scancode == SDL_SCANCODE_W); ///input detection ;
		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

