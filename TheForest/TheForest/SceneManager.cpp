#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(double DeltaTime)
{
	player.Update(DeltaTime);
	
}

void SceneManager::Draw()
{
	for (int i = 0; i < renderers.size(); i++)
	{
		renderers[i].Animate();
	}

}

void SceneManager::StartGame()
{
}
