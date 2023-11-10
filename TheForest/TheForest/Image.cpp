#include "Image.h"

#include <iostream>

#include "RendererSingleton.h"

Image::Image()
{
}

Image::Image(const char* filePath)
{
	imagePath = filePath;
	SDL_Surface* image = IMG_Load(imagePath);
	
	texture = SDL_CreateTextureFromSurface(GameRenderer::GetRenderer(), image);
	size = Vector2(image->w, image->h);
	
	SDL_FreeSurface(image);
}