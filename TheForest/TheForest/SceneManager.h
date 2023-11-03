#pragma once
#include "Player.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update(double DeltaTime);
	void Draw();

private:
	void StartGame();

	Player player;
	std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
};