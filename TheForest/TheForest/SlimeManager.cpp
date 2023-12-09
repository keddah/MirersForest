#include "SlimeManager.h"

SlimeManager::SlimeManager(Player& plyr, std::vector<Tile>& floorRef): tiles(floorRef), player(plyr)
{
    const auto slime1 = new Slime(player, tiles);
    const auto slime2 = new Slime(player, tiles);
    const auto slime3 = new Slime(player, tiles);

    slime1->SetPosition(500, 0);
    slime2->SetPosition(900, 0);
    slime3->SetPosition(100, 0);

    slimes.push_back(slime1);
    slimes.push_back(slime2);
    slimes.push_back(slime3);
}

void SlimeManager::Update(float deltaTime)
{
    for(int i = 0; i < slimes.size(); i++)
    {
        slimes[i]->Update(deltaTime);
        if(slimes[i]->IsDead()) slimes.erase(slimes.begin() + i);
    }
}


