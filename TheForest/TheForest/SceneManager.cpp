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

	print(colliders[0].Overlapping(colliders[1]));
	
	for (const auto& collider : colliders)
	{
		 player.GetCollider().obstructed = true;
	}
}

void SceneManager::Draw()
{
	for (auto& renderer : renderers)
	{
		renderer.Animate();
	}

	for (auto& collider : colliders)
	{
		if (collider.IsDebugging()) collider.Debug();
	}
}

void SceneManager::StartGame()
{
	const Collision floor = Collision(100,0,100,1100);
	colliders.push_back(floor);

	colliders.push_back(player.GetCollider());	
}
