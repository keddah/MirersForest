#pragma once
#include "AudioManager.h"
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
    AudioManager audio;
    Player player = Player(tileManager.GetTiles(), currentSlide, audio);
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles(), audio);
    FlowerManager flowerManager = FlowerManager(player);
    UserInterface ui = UserInterface(player);
    
};
