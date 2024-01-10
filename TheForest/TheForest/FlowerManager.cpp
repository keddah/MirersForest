/**************************************************************************************************************
* Flower Manager - Code
*
* The code file for the Flower manager class. Responsible for spawning, updating and drawing all of the flowers that it creates. Also
* handles when to draw/update the flower depending on which slide the player is on. 
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#include "FlowerManager.h"

#include "GameSingletons.h"

FlowerManager::FlowerManager(Player& player) : rPlayer(player)
{
    
}

void FlowerManager::FixedUpdate(float deltaTime)
{
    // Only update if on the correct slide
    for (auto& flower : flowers) if(flower.GetLevelSlide() == levelSlide) flower.Update(deltaTime);
}

void FlowerManager::Draw()
{
    for(auto& flower : flowers)
    {
        if(flower.GetLevelSlide() == levelSlide) flower.Draw();
    }
}

void FlowerManager::SetLevelSlide(const short slide)
{
    // Only do anything if it's a new slide
    if(slide == levelSlide) return;

    const int screenWidth = GameWindow::GetWindowWidth(); 
    
    // Going to the next area means that the inputted slide is further ahead than the current one
    const bool next = slide > levelSlide;

    // If going to the next slide... while the current slide is less than parameter slide... (otherwise opposite)
    // (Spawning on a random slide doesn't break the game)
    while(next? levelSlide < slide : levelSlide > slide)
    {
        for (auto& flower : flowers)
        {
            // Move every tile left/right (keeping their Y value)
            flower.SetPosition({flower.GetPosition().x + (next? -screenWidth: screenWidth), flower.GetPosition().y});
        }
        levelSlide += next? 1 : -1;
    }
}

void FlowerManager::Reset()
{
    const int screenWidth = GameWindow::GetWindowWidth();
    
    while(levelSlide != 0)
    {
        for (auto& flower : flowers)
        {
            // Move every tile left/right (keeping their Y value)
            flower.SetPosition({flower.GetPosition().x + screenWidth, flower.GetPosition().y});
        }
        levelSlide--;
    }
}

void FlowerManager::SpawnFlowers(short lvlIndex, const bool reset)
{
    if(reset)
    {
        levelSlide = 0;
        flowers.clear();
    }
    
    switch (lvlIndex)
    {
    case 0:
        Level1Flowers();
        break;

    case 1:
        Level2Flowers();
        break;

    default:
        Level1Flowers();
        break;
    }

    const int width = GameWindow::GetWindowWidth();
    for (auto& flower : flowers)
    {
        flower.SetSlide(static_cast<short>(floor(flower.GetPosition().x / width)));
    }
}

void FlowerManager::Level1Flowers()
{
    const FlowerUp one = FlowerUp(rPlayer, {1750, 228});
    const FlowerUp two = FlowerUp(rPlayer, Vector2(GameWindow::GetWindowWidth() * 2 + 900, 450));
    const FlowerUp three = FlowerUp(rPlayer, Vector2( GameWindow::GetWindowWidth() * 4 + 1550, 520));

    flowers.push_back(one);
    flowers.push_back(two);
    flowers.push_back(three);
}

void FlowerManager::Level2Flowers()
{
    const int screenWidth = GameWindow::GetWindowWidth(); 
    //\\//\\//\\//\\// 3rd Slide //\\//\\//\\//\\// 

    const FlowerUp one = FlowerUp(rPlayer, Vector2( screenWidth * 2 + 100, 770));
    flowers.push_back(one);

    const FlowerUp two = FlowerUp(rPlayer, Vector2(screenWidth * 2 + 1400, 990));
    flowers.push_back(two);


    //\\//\\//\\//\\// 4th Slide //\\//\\//\\//\\// 

    const FlowerUp three = FlowerUp(rPlayer, Vector2(screenWidth * 3 + 400, 570));
    flowers.push_back(three);


    //\\//\\//\\//\\// 5th Slide //\\//\\//\\//\\// 

    const FlowerUp four = FlowerUp(rPlayer, Vector2(screenWidth * 4 + 1700, 420));
    flowers.push_back(four);

    
    //\\//\\//\\//\\// 7th Slide //\\//\\//\\//\\// 

    const FlowerUp five = FlowerUp(rPlayer, Vector2(screenWidth * 6 + 500, 870));
    flowers.push_back(five);
}


//\\//\\//\\//\\\\//\\__ FlowerUp __//\\//\\//\\//\\\\//\\

FlowerManager::FlowerUp::FlowerUp(Player& player, Vector2 pos): position(pos), rP(player)
{
    renderer.SetVisibility(true);
}

void FlowerManager::FlowerUp::Update(float deltaTime)
{
    // Flowers can respawn in case the player misses a jump... (instead of restarting, they'd wait)
    Respawn(deltaTime);
    
    if(used) return;
    
    rect.x = position.x;
    rect.y = position.y;
    rect.w = renderer.GetDrawSize().x;
    rect.h = renderer.GetDrawSize().y;

    Interaction();
}

void FlowerManager::FlowerUp::Interaction()
{
    if(rP.IsDead()) return;
    
    // When there is an interaction
    if(!SDL_HasIntersectionF(&rP.GetRect(), &rect)) return;

    if(rP.GivePowerup()) used = true;
}

void FlowerManager::FlowerUp::Respawn(float deltaTime)
{
    if(!used) return;

    respawnTimer += deltaTime;
    if(respawnTimer < respawnDelay) return;
    
    respawnTimer = 0;
    used = false;
}
