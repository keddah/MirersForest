#pragma once

#include <SDL_Image.h>
#include "Vector2.h"

class Image
{
public:
	Image();
	Image(const char* filePath);

	~Image() { SDL_DestroyTexture(texture); }

	SDL_Texture* GetTexture() const { return texture; }
	const char* GetImagePath() const { return imagePath; }
	Vector2& GetImageSize() { return size; }
	
private:
	SDL_Texture* texture;
	const char* imagePath; 
	Vector2 size = Vector2();

};

