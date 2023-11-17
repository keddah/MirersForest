#include "SceneManager.h"

#include "GameSingletons.h"

SceneManager::SceneManager()
{
	renderers.push_back(player.GetRenderer());
	StartGame();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(float deltaTime)
{
	player.Update(deltaTime);
	collisionManager.Update();
}

void SceneManager::Draw()
{
	for (auto& renderer : renderers)
	{
		renderer.Animate();
	}

	collisionManager.Debug();
}

void SceneManager::StartGame()
{
	collisionManager.AddCollider(player);	

	_floor1.SetSolid(true);
	collisionManager.AddCollider(_floor1);	
	
}
