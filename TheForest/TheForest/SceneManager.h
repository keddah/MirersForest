#pragma once

#include "SpriteRenderer.h"
#include "Player.h"

#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update(float deltaTime);
	void Draw();

private:
	void StartGame();
	Collision floor;
	Player player;

	CollisionManager collisionManager;
	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};