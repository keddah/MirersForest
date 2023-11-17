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
	collisionManager.Update(deltaTime);
	// print("rect: (" << colliders[0].GetRect().x<< ", " << colliders[0].GetRect().y << ", " << colliders[0].GetRect().w << ", " << colliders[0].GetRect().h << ")\n")
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
	const Collision& playerCollision = player.GetCollider();
	collisionManager.AddCollider(playerCollision);	

	floor = Collision(100,0,100,1100);
	collisionManager.AddCollider(floor);	
}
