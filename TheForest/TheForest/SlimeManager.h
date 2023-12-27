/**************************************************************************************************************
* Slime Manager - Header
*
* The header file for the Slime manager class. Responsible for creating object references that each slime will need
* in order to be created. Also creates functions that handle the creation / management of slimes.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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
