#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(const char* filePath, SDL_Renderer* rndrr)
{
	SDL_Surface* image = IMG_Load(filePath);
	texture = SDL_CreateTextureFromSurface(rndrr, image);
	
	size = Vector2(image->w, image->h);
	
	SDL_FreeSurface(image);

}