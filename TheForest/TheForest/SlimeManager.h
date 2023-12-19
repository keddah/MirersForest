#pragma once
#include <vector>

#include "Slime.h"

class SlimeManager
{
public:
    SlimeManager(Player& plyr, std::vector<Tile>& floorRef, const AudioManager& sound);
    const std::vector<Slime*>& GetSlimes() { return slimes; }
    
    void Update(float deltaTime);
    void Draw() const;

    void SetLevelSlide(short slide);
    void SpawnSlimes(short levelIndex);
    
private:
    std::vector<Slime*> slimes = std::vector<Slime*>();

    std::vector<Tile>& tiles; 
    Player& rPlayer;
    const AudioManager& rAudio;
    
    short levelSlide;

    void SpawnLevel1();
};
