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
	Collision _floor1 = Collision(0,700,1600,100);
	Collision _floor3 = Collision(900,980,100,100);
	Collision _floor2 = Collision(900,980,100,100);
	Collision _floor4 = Collision(1500,980,100,100);
	Player player;

	CollisionManager collisionManager;
	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};