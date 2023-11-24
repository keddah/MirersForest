#pragma once

#include <SDL_render.h>

#include "Vector2.h"
#include "SpriteSheet.h"


class Image
{
public:
	Image() = default;
	Image(const char* filePath);

	~Image() 
	{ 
		SDL_DestroyTexture(texture); 
	}

	SpriteSheet& GetSpriteSheet() { return spriteSheet; }
	void SetSpriteCount(short count);

	SDL_Texture* GetTexture() const { return texture; }
	const char* GetImagePath() const { return imagePath; }
	
private:
	const char* imagePath; 
	SDL_Texture* texture;
	
	SpriteSheet spriteSheet;
	
	Vector2 size;
};

