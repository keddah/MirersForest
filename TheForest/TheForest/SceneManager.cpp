#include "SceneManager.h"

SceneManager::SceneManager()
{
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
	collisionManager.Debug();
	
	for (auto& renderer : renderers) renderer.Draw();
}

void SceneManager::StartGame()
{
	// collisionManager.AddCollider(floor2);
	// collisionManager.AddCollider(floor4);
	// collisionManager.AddCollider(floor1);	
	// collisionManager.AddCollider(floor3);	
	
	collisionManager.AddCollider(player);
	
	floor4.SetDebugColour(SDL_Rect{80,80,80,255});
	floor2.SetDebugColour(SDL_Rect{80,80,80,255});
	floor3.SetDebugColour(SDL_Rect{80,80,80,255});

	for(auto& tile : tileManager.GetTiles()) collisionManager.AddCollider(tile.GetCollider());

	// Since every collider will have a renderer...
	for(auto& collider : collisionManager.GetColliders())
	{
		// Get the collider's renderer and add it to the vector of renderers
		renderers.push_back(collider.GetRenderer());
	}

}
