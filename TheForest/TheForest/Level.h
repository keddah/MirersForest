#pragma once
#include "FlowerManager.h"
#include "Player.h"
#include "SlimeManager.h"
#include "TileManager.h"
#include "UserInterface.h"

class Level
{
public:
    Level(short lvlNum);

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void DrawSlide();
    
private:
    ManualRenderer bkg = ManualRenderer("Sprites/background.jpg", {0,0});

    void SyncSlides();
    
    // std::vector<Slide> slides = std::vector<Slide>(); 
    short currentSlide = 0;
    
    TileManager tileManager;
    Player player = Player(tileManager.GetTiles(), currentSlide);
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles());
    FlowerManager flowerManager = FlowerManager(player);
    UserInterface ui = UserInterface(player);
    
};
