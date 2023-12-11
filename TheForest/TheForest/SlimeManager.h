#pragma once
#include <vector>

#include "Slime.h"

class SlimeManager
{
public:
    SlimeManager(Player& plyr, std::vector<Tile>& floorRef);
    const std::vector<Slime*>& GetSlimes() { return slimes; }
    
    void Update(float deltaTime);
    void Draw() const { for(const auto& slime : slimes) if(slime->GetLevelSlide() == levelSlide) slime->Draw(); }

    void SetLevelSlide(const short slide) { levelSlide = slide; }
    
private:
    std::vector<Slime*> slimes = std::vector<Slime*>();

    std::vector<Tile>& tiles; 
    Player& player;

    short levelSlide;
};
