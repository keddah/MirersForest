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
	Player player = Player(collisionManager.GetColliders());
	Collision floor1 = Collision(collisionManager.GetColliders(), 0,700,1600,100);
	Collision floor2 = Collision(collisionManager.GetColliders(), 900,600,100,100);
	Collision floor3 = Collision(collisionManager.GetColliders(), 900,980,100,100);
	Collision floor4 = Collision(collisionManager.GetColliders(), 1500,980,100,100);

	
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};