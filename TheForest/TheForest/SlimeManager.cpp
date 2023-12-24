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

    while(next? levelSlide < slide : levelSlide > slide)
    {
        if(!resetting)
        {
            for (const auto& slime : slimes)
            {
                // Move every slime left/right (keeping their Y value)
                slime->SetPosition({slime->GetPosition().x + (next? -GameWindow::GetWindowWidth(): GameWindow::GetWindowWidth()), slime->GetPosition().y});
            }
        }
        levelSlide += next? 1 : -1;
    }
    
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

        case 1:
            SpawnLevel2();
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

    const auto slime4 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime5 = new Slime(rPlayer, rTiles, rAudio);
    
    const auto slime6 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime7 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime8 = new Slime(rPlayer, rTiles, rAudio);
    const auto slime9 = new Slime(rPlayer, rTiles, rAudio);
    
    const auto slime10 = new Slime(rPlayer, rTiles, rAudio);

    // Slide 1
    slime1->SetPosition(400, 0);
    slime2->SetPosition(550, 0);
    slime3->SetPosition(900, 0);

    // Slide 3
    slime4->SetPosition(GameWindow::GetWindowWidth() * 2 + 600, 730);
    slime5->SetPosition(GameWindow::GetWindowWidth() * 2 + 1350, 400);

    // Slide 5
    slime6->SetPosition(GameWindow::GetWindowWidth() * 4 + 330, 900);
    slime7->SetPosition(GameWindow::GetWindowWidth() * 4 + 1000, 500);
    slime8->SetPosition(GameWindow::GetWindowWidth() * 4 + 1580, 300);
    slime9->SetPosition(GameWindow::GetWindowWidth() * 4 + 1800, 500);

    // Slide 6
    slime10->SetPosition(GameWindow::GetWindowWidth() * 5 + 1000, 700);

    
    slimes.push_back(slime1);
    slimes.push_back(slime2);
    slimes.push_back(slime3);
    
    slimes.push_back(slime4);
    slimes.push_back(slime5);
    
    slimes.push_back(slime6);
    slimes.push_back(slime7);
    slimes.push_back(slime8);
    slimes.push_back(slime9);
    
    slimes.push_back(slime10);

    slime4->SetPatrol({{1100, slime4->GetPosition().y}, {600, slime4->GetPosition().y}}, 6);

    slime6->SetPatrol({{900, slime6->GetPosition().y}, {330, slime6->GetPosition().y}}, 3, .015f);
    slime7->SetPatrol({{1250, slime7->GetPosition().y}, {1000, slime7->GetPosition().y}}, .5f, .0125f);
    slime8->SetPatrol({{1300, slime8->GetPosition().y}, {1580, slime8->GetPosition().y}});
}

void SlimeManager::SpawnLevel2()
{
    //\\//\\//\\//\\// 1st Slide //\\//\\//\\//\\// 

    const auto slime1 = new Slime(rPlayer, rTiles, rAudio);
    slime1->SetPosition(300, 0);
    slimes.push_back(slime1);
    slime1->SetPatrol({{700, slime1->GetPosition().y}, slime1->GetPosition()}, 3);

    const auto slime2 = new Slime(rPlayer, rTiles, rAudio);
    slime2->SetPosition(800, 0);
    slimes.push_back(slime2);
    slime2->SetPatrol({{1100, slime2->GetPosition().y}, slime2->GetPosition()}, 0);

    const auto slime3 = new Slime(rPlayer, rTiles, rAudio);
    slime3->SetPosition(1200, 0);
    slimes.push_back(slime3);
    slime3->SetPatrol({{1500, slime3->GetPosition().y}, slime3->GetPosition()}, 0);

    const auto slime4 = new Slime(rPlayer, rTiles, rAudio);
    slime4->SetPosition(1570, 0);
    slimes.push_back(slime4);
    slime4->SetPatrol({{1850, slime4->GetPosition().y}, slime4->GetPosition()}, 3);

    
    //\\//\\//\\//\\// 2nd Slide //\\//\\//\\//\\// 

    const auto slime5 = new Slime(rPlayer, rTiles, rAudio);
    slime5->SetPosition(GameWindow::GetWindowWidth() + 200, 0);
    slimes.push_back(slime5);


    //\\//\\//\\//\\// 3rd Slide //\\//\\//\\//\\// 

    const auto slime6 = new Slime(rPlayer, rTiles, rAudio);
    slime6->SetPosition(GameWindow::GetWindowWidth() * 2 + 300, 0);
    slimes.push_back(slime6);
    slime6->SetPatrol({Vector2(600, slime6->GetPosition().y), Vector2(300, slime6->GetPosition().y)}, 4, .022f);

    const auto slime7 = new Slime(rPlayer, rTiles, rAudio);
    slime7->SetPosition(GameWindow::GetWindowWidth() * 2 + 1340, 0);
    slimes.push_back(slime7);

    const auto slime8 = new Slime(rPlayer, rTiles, rAudio);
    slime8->SetPosition(GameWindow::GetWindowWidth() * 2 + 1440, 0);
    slimes.push_back(slime8);

    
    //\\//\\//\\//\\// 4th Slide //\\//\\//\\//\\// 

    const auto slime9 = new Slime(rPlayer, rTiles, rAudio);
    slime9->SetPosition(GameWindow::GetWindowWidth() * 3 + 800, 0);
    slimes.push_back(slime9);

    const auto slime10 = new Slime(rPlayer, rTiles, rAudio);
    slime10->SetPosition(GameWindow::GetWindowWidth() * 3 + 950, 0);
    slimes.push_back(slime10);
    slime10->SetPatrol({Vector2(1100, slime10->GetPosition().y), Vector2(950, slime10->GetPosition().y)}, 4);
    
    const auto slime11 = new Slime(rPlayer, rTiles, rAudio);
    slime11->SetPosition(GameWindow::GetWindowWidth() * 3 + 1550, 0);
    slimes.push_back(slime11);

    
    //\\//\\//\\//\\// 5th Slide //\\//\\//\\//\\// 

    const auto slime12 = new Slime(rPlayer, rTiles, rAudio);
    slime12->SetPosition(GameWindow::GetWindowWidth() * 4 + 1100, 800);
    slimes.push_back(slime12);

    
    //\\//\\//\\//\\// 6th Slide //\\//\\//\\//\\// 

    const float start = GameWindow::GetWindowWidth() * 5 + 200;
    for(short i = 0; i < 18; i++)
    {
        constexpr float space = 10;
        const auto newSlime = new Slime(rPlayer, rTiles, rAudio);
        newSlime->SetPosition(start + i * (newSlime->GetRenderer().GetDrawSize().x + space), 0);
        newSlime->SetGravity(false);
        slimes.push_back(newSlime);
    }
}


