#include "SlimeManager.h"

#include "GameSingletons.h"

SlimeManager::SlimeManager(Player& plyr, std::vector<Tile>& floorRef, const AudioManager& sound): rTiles(floorRef), rPlayer(plyr), rAudio(sound)
{
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

void SlimeManager::Draw() const
{
    for(const auto& slime : slimes)
    {
        if(slime->GetLevelSlide() == levelSlide)
        {
            slime->Draw();
            slime->DeathAnimation();
        }
    }
}

void SlimeManager::SetLevelSlide(const short slide)
{
    if(slide == levelSlide) return;
    
    const bool next = slide > levelSlide;
    if(!resetting)
    {
        for (const auto& slime : slimes)
        {
            slime->SetPosition({slime->GetPosition().x + (next? -GameWindow::GetWindowWidth() : GameWindow::GetWindowWidth()), slime->GetPosition().y});
        }
    }
    
    levelSlide = slide;
    resetting = false;
}

void SlimeManager::Reset(short lvlIndex)
{
    slimes.clear();
    SpawnSlimes(lvlIndex);
    resetting = true;
}

void SlimeManager::SpawnSlimes(short levelIndex)
{
    switch (levelIndex)
    {
        case 0:
            SpawnLevel1();
            break;

        default:
            SpawnLevel1();
            break;
    }

    for (const auto& slime : slimes)
    {
        slime->SetSlide(floor(slime->GetPosition().x / GameWindow::GetWindowWidth()));
    }
}

void SlimeManager::SpawnLevel1()
{
    const auto slime1 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime2 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime3 = new Slime(rPlayer, rTiles, rAudio);

    slime1->SetPosition(400, 0);
    slime2->SetPosition(550, 0);
    slime3->SetPosition(900, 0);

    slimes.push_back(slime1);
    slimes.push_back(slime2);
    slimes.push_back(slime3);
}


