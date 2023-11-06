#pragma once

#include "SpriteRenderer.h"
#include "Player.h"

#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update(double DeltaTime);
	void Draw();

private:
	void StartGame();

	Player* player;
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};