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
    std::vector<SpriteRenderer> spriteRenderers = std::vector<SpriteRenderer>();
    std::vector<StaticRenderer> staticRenderers = std::vector<StaticRenderer>();
    
    Player player = Player(tileManager.GetTiles());
};
