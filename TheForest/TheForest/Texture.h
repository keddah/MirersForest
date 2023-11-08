#pragma once

#include <SDL_Image.h>
#include "Vector2.h"

class Texture
{
public:
	Texture();
	Texture(const char* filePath, SDL_Renderer* rndrr);

	~Texture() { SDL_DestroyTexture(texture); };

	SDL_Texture* GetTexture() { return texture; }

private:
	SDL_Texture* texture;
	
	Vector2 size = Vector2();

};

