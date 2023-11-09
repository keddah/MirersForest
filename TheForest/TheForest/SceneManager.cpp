#include "SceneManager.h"

SceneManager::SceneManager()
{
	renderers.push_back(player.GetRenderer());
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
	for (auto& renderer : renderers) renderer.Animate();

}

void SceneManager::StartGame()
{
}
