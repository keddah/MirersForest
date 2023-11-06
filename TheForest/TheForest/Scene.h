#pragma once
#include "SpriteRenderer.h"

class Scene
{
public: 
	Scene(short levelNum);
	~Scene();

private:
	SpriteRenderer bkgRenderer;
	
};
