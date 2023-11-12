#include "Image.h"

#include <iostream>

#include "GameSingletons.h"

Image::Image()
{
}

Image::Image(const char* filePath)
{
	imagePath = filePath;
	SDL_Surface* image = IMG_Load(imagePath);
	
	texture = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);
	size = Vector2(image->w, image->h);
	
	SDL_FreeSurface(image);

	spriteSheet.SetImageSize(size);
}

void Image::SetSpriteCount(short count)
{
	spriteSheet.SetFrameCount(count);
}
