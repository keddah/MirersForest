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
	Collision _floor1 = Collision(300,400,100,300);
	Player player;

	CollisionManager collisionManager;
	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};