#pragma once
#include "Player.h"
#include "TileManager.h"

class GameSession
{
public:
    GameSession();
    ~GameSession() = default;

    void Update(float deltaTime);
    void Draw();
    
private:
    TileManager tileManager;
    std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
    
    Player player = Player(tileManager.GetTiles());
};
