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
	Collision _floor1 = Collision(0,700,1000,100);
	Collision _floor2 = Collision(700,0,100,1100);
	Player player;

	CollisionManager collisionManager;
	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};