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
	_floor1.SetSolid(true);
	collisionManager.AddCollider(_floor3);	
	collisionManager.AddCollider(_floor4);
	collisionManager.AddCollider(_floor2);
	collisionManager.AddCollider(_floor1);	
	
	_floor4.SetDebugColour(SDL_Rect{80,80,80,80});
	_floor2.SetDebugColour(SDL_Rect{80,80,80,80});
	_floor3.SetDebugColour(SDL_Rect{80,80,80,80});

	
	collisionManager.AddCollider(player);	

}
