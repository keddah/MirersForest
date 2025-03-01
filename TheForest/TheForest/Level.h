/**************************************************************************************************************
* Level - Header
*
* The header file for the Level class. Creates objects for the player, tile manager, slime manager, flower manager, audio manager
* and UI. Also manages going to the next level and ensuring that all the managers have the same level slide.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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
    Level(short lvlNum = 0);
    
    void FixedUpdate(float deltaTime);
    void Update(float deltaTime);
    void Draw();

private:
    // This constructor for the spriteRenderer needs a reference (this is the reference) 
    Vector2 empty;
    const std::vector<std::string> backgrounds = {"Sprites/background.jpg", "Sprites/caveBkg.jpg"};
    SpriteRenderer bkg = SpriteRenderer(backgrounds, empty, false);

    void SyncSlides();
    void NextLevel();
    
    const short levelCount = 2;
    short currentLevel = 0;
    short currentSlide = 0;
    bool completed = false;

    TileManager tileManager;
    AudioManager audio;
    Player player = Player(tileManager.GetTiles(), currentSlide, audio);
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles(), audio);
    FlowerManager flowerManager = FlowerManager(player);
    UserInterface ui = UserInterface(player);
};
