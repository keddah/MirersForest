#pragma once
#include <vector>

#include "Slime.h"

class SlimeManager
{
public:
    SlimeManager(Player& plyr, std::vector<Tile>& floorRef, const AudioManager& sound);
    const std::vector<Slime*>& GetSlimes() { return slimes; }
    
    void FixedUpdate(float deltaTime);
    void Draw() const;

    void SetLevelSlide(short slide);
    void SpawnSlimes(short levelIndex);

    void Reset(short lvlIndex);
    
private:
    std::vector<Slime*> slimes = std::vector<Slime*>();

    std::vector<Tile>& rTiles; 
    Player& rPlayer;
    const AudioManager& rAudio;

    bool resetting = false;
    short levelSlide;

    void SpawnLevel1();
    void SpawnLevel2();
};
