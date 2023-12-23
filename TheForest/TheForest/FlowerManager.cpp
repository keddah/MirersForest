#include "FlowerManager.h"

#include "GameSingletons.h"

FlowerManager::FlowerManager(Player& player) : rPlayer(player)
{
    
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

    const bool next = slide > levelSlide;

    while(next? levelSlide < slide : levelSlide > slide)
    {
        for (auto& flower : flowers)
        {
            // Move every tile left/right (keeping their Y value)
            flower.SetPosition({flower.GetPosition().x + (next? -GameWindow::GetWindowWidth(): GameWindow::GetWindowWidth()), flower.GetPosition().y});
        }
        levelSlide += next? 1 : -1;
    }
}

void FlowerManager::SpawnFlowers(short lvlIndex, const bool reset)
{
    if(reset) flowers.clear();
    
    switch (lvlIndex)
    {
    case 0:
        Level1Flowers();
        break;

    case 1:
        Level1Flowers();
        break;

    default:
        Level1Flowers();
        break;
    }
}

void FlowerManager::Level1Flowers()
{
    FlowerUp one = FlowerUp(rPlayer, {1750, 228});
    FlowerUp two = FlowerUp(rPlayer, Vector2(GameWindow::GetWindowWidth() * 2 + 900, 450));
    FlowerUp three = FlowerUp(rPlayer, Vector2( GameWindow::GetWindowWidth() * 4 + 1550, 520));
    // FlowerUp four = FlowerUp(rPlayer, Vector2( GameWindow::GetWindowWidth() * 5 + 420, 970));

    flowers.push_back(one);
    flowers.push_back(two);
    flowers.push_back(three);
    // flowers.push_back(four);
}

void FlowerManager::Level2Flowers()
{
}


void FlowerManager::Reset()
{
    while(levelSlide != 0)
    {
        for (auto& flower : flowers)
        {
            flower.Reset();

            // Move every tile left/right (keeping their Y value)
            flower.SetPosition({flower.GetPosition().x + GameWindow::GetWindowWidth(), flower.GetPosition().y});
        }
        levelSlide--;
    }
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
