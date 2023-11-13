#pragma once

#include "SpriteRenderer.h"
#include "Player.h"

#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update(float DeltaTime);
	void Draw();

private:
	void StartGame();

	Player player;
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
	std::vector<Collision> colliders = std::vector<Collision>();
};