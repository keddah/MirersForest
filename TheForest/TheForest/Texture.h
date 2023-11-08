#pragma once
#include <SDL.h>
class Texture
{
public:
	Texture(const char* filePath, SDL_Renderer* rndrr);
	~Texture() { SDL_DestroyTexture(texture); };

	SDL_Texture* GetTexture() { return texture; }

private:
	SDL_Texture* texture;
};

