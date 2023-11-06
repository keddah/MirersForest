#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(double DeltaTime)
{
	if(player) player->Update(DeltaTime);
	
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
