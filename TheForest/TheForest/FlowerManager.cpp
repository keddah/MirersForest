#include "FlowerManager.h"

#include "GameSingletons.h"

FlowerManager::FlowerManager(Player& player) : rPlayer(player)
{
    FlowerUp one = FlowerUp(rPlayer, {500, 700});
    FlowerUp two = FlowerUp(rPlayer, {900, 700});
    FlowerUp three = FlowerUp(rPlayer, {2500, 700});
    FlowerUp four = FlowerUp(rPlayer, {3200, 700});

    flowers.push_back(one);
    flowers.push_back(two);
    flowers.push_back(three);
    flowers.push_back(four);
}

void FlowerManager::Update(float deltaTime)
{
    // Only update if on the correct slide
    for (auto& flower : flowers) if(flower.GetLevelSlide() == levelSlide) flower.Update(deltaTime);
}

void FlowerManager::Draw()
{
    for (auto& flower : flowers)
    {
        // Draw the flower if its on the correct slide
        if(flower.GetLevelSlide() == levelSlide) flower.Draw(); 
    }
}

void FlowerManager::SetLevelSlide(const short slide)
{
    if(slide == levelSlide) return;

    int screenWidth;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, nullptr);
    
    const bool next = slide > levelSlide;
    for (auto& flower : flowers)
    {
        flower.SetPosition({flower.GetPosition().x + (next? -screenWidth : screenWidth), flower.GetPosition().y});
    }
    
    levelSlide = slide;
}



//\\//\\//\\//\\\\//\\__ FlowerUp __//\\//\\//\\//\\\\//\\

FlowerManager::FlowerUp::FlowerUp(Player& player, Vector2 pos): position(pos), rP(player)
{
    int screenWidth;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, nullptr);
    levelSlide = floor(position.x / screenWidth);
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
