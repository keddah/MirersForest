#include "Image.h"
#include <SDL_image.h>
#include "GameSingletons.h"


Image::Image(const char* filePath)
{
	imagePath = filePath;

	SDL_Surface* image = IMG_Load(filePath);
	
	texture = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), image);

	if(!image) print("IMAGE INVALID")
	if(!texture) print("TEXTURE INVALID")
	if(!GameWindow::GetRenderer()) print("RENDERER INVALID")

	size = Vector2(image->w, image->h);

	
	SDL_FreeSurface(image);
	
	spriteSheet.SetImageSize(size);
}

void Image::SetSpriteCount(short count)
{
	spriteSheet.SetFrameCount(count);
}
