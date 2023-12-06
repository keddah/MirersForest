#pragma once
#include "Player.h"
#include "TileManager.h"

class GameSession
{
public:
    GameSession();
    ~GameSession() = default;

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Draw();
    
private:
    TileManager tileManager;
    std::vector<SpriteRenderer> spriteRenderers = std::vector<SpriteRenderer>();
    std::vector<ManualRenderer> manualRenderers = std::vector<ManualRenderer>();

    ManualRenderer bkg = ManualRenderer("Sprites/background.jpg", {0,0});
    
    Player player = Player(tileManager.GetTiles());
};
