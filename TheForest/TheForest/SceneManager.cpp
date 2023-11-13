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

	for (const auto& collider : colliders)
	{
		if(player.Overlapping(collider)) player.moveController.grounded = true;
	}
}

void SceneManager::Draw()
{
	for (auto& renderer : renderers) renderer.Animate();
}

void SceneManager::StartGame()
{
	Collision floor = Collision(SDL_Rect{1920,1080, 1920, 100});
	colliders.push_back(floor);
}
