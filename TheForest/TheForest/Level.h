#pragma once
#include "Player.h"
#include "SlimeManager.h"
#include "TileManager.h"

class Level
{
public:
    Level(short lvlNum);

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Draw();
    
    const std::vector<ManualRenderer>& GetManualRenderers() { return manuals; } 
    const std::vector<SpriteRenderer>& GetSpriteRenderers() { return sprites; } 
    
private:
    class Slide
    {
    public:

    private:
        
    };
    ManualRenderer bkg = ManualRenderer("Sprites/background.jpg", {0,0});

    std::vector<Slide> slides = std::vector<Slide>(); 
    short currentSlide = 0;
    
    TileManager tileManager;
    Player player = Player(tileManager);
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles());

    std::vector<ManualRenderer> manuals = std::vector<ManualRenderer>();
    std::vector<SpriteRenderer> sprites = std::vector<SpriteRenderer>();
};
