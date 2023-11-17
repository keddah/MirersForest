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
	
	collisionManager.AddCollider(_floor1);	
	
}
