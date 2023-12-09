#pragma once
#include "Player.h"
#include "SlimeManager.h"
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
    Player player = Player(tileManager.GetTiles());
    
    std::vector<SpriteRenderer> spriteRenderers = std::vector<SpriteRenderer>();
    std::vector<ManualRenderer> manualRenderers = std::vector<ManualRenderer>();

    ManualRenderer bkg = ManualRenderer("Sprites/background.jpg", {0,0});
    
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles());
};
