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

void SceneManager::Update(float DeltaTime)
{
	player.Update(DeltaTime);

	//print(colliders[0].Overlapping(colliders[1]));
	
	for (const auto& collider : colliders)
	{
		// player.GetCollider().obstructed = true;
	}
}

void SceneManager::Draw()
{
	for (auto& renderer : renderers) renderer.Animate();
}

void SceneManager::StartGame()
{
	const Collision floor = Collision(0,440,1920,100);
	colliders.push_back(floor);

	colliders.push_back(player.GetCollider());	
}
