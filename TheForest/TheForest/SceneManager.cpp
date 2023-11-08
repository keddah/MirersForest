#include "SceneManager.h"

SceneManager::SceneManager()
{
	//player = Player();
}

SceneManager::~SceneManager()
{
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
