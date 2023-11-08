#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	//delete player;
}

void SceneManager::Update(float DeltaTime)
{
	player.Update(DeltaTime);
	
}

void SceneManager::Draw()
{
	for (auto& renderer : renderers)
	{
		renderer.Animate();
	}

}

void SceneManager::StartGame()
{
}
