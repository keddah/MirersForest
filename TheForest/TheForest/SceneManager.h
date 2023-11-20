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
	CollisionManager collisionManager;
	Collision _floor1 = Collision(collisionManager.GetColliders(), 0,700,1600,100);
	Collision _floor3 = Collision(collisionManager.GetColliders(), 900,980,100,100);
	Collision _floor2 = Collision(collisionManager.GetColliders(), 900,980,100,100);
	Collision _floor4 = Collision(collisionManager.GetColliders(), 1500,980,100,100);
	Player player = Player(collisionManager.GetColliders());

	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};