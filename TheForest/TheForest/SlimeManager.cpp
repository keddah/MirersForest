#include "SlimeManager.h"

#include "GameSingletons.h"

SlimeManager::SlimeManager(Player& plyr, std::vector<Tile>& floorRef): tiles(floorRef), player(plyr)
{
    const auto slime1 = new Slime(player, tiles);
    const auto slime2 = new Slime(player, tiles);
    const auto slime3 = new Slime(player, tiles);
    const auto slime4 = new Slime(player, tiles);
    const auto slime5 = new Slime(player, tiles);
    const auto slime6 = new Slime(player, tiles);
    const auto slime7 = new Slime(player, tiles);
    const auto slime8 = new Slime(player, tiles);

    slime1->SetPosition(500, 0);
    slime2->SetPosition(900, 0);
    slime3->SetPosition(100, 0);
    slime4->SetPosition(3000, 0);
    slime5->SetPosition(1000, 0);
    slime6->SetPosition(600, 0);
    slime7->SetPosition(700, 0);
    slime8->SetPosition(800, 0);

    slimes.push_back(slime1);
    slimes.push_back(slime2);
    slimes.push_back(slime3);
    slimes.push_back(slime4);
    slimes.push_back(slime5);
    slimes.push_back(slime6);
    slimes.push_back(slime7);
    slimes.push_back(slime8);

    for (const auto& slime : slimes)
    {
        slime->SetSlide(floor(slime->GetPosition().x / GameWindow::GetWindowSize().x));
    }
}

void SlimeManager::Update(float deltaTime)
{
    for(int i = 0; i < slimes.size(); i++)
    {
        if(slimes[i]->GetLevelSlide() != levelSlide) continue;
        
        slimes[i]->Update(deltaTime);
        if(slimes[i]->IsDead()) slimes.erase(slimes.begin() + i);
    }
}

void SlimeManager::SetLevelSlide(const short slide)
{
    if(slide == levelSlide) return;
    
    const bool next = slide > levelSlide;
    for (const auto& slime : slimes)
    {
        slime->SetPosition({slime->GetPosition().x + (next? -GameWindow::GetWindowSize().x : GameWindow::GetWindowSize().x), slime->GetPosition().y});
    }
    
    levelSlide = slide;
}


