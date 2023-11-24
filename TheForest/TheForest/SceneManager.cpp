#include "SceneManager.h"

#include "GameSingletons.h"

SceneManager::SceneManager()
{
	StartGame();
	renderers.push_back(player.GetRenderer());
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
	collisionManager.AddCollider(floor2);
	collisionManager.AddCollider(floor4);
	collisionManager.AddCollider(floor1);	
	collisionManager.AddCollider(floor3);	
	
	floor4.SetDebugColour(SDL_Rect{80,80,80,80});
	floor2.SetDebugColour(SDL_Rect{80,80,80,80});
	floor3.SetDebugColour(SDL_Rect{80,80,80,80});
	
	collisionManager.AddCollider(player);
	
	for(auto& tile : tileManager.GetTiles()) collisionManager.AddCollider(tile.GetCollider());

}
