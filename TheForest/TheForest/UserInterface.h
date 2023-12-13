#pragma once
#include "Player.h"
#include "Renderers.h"

class UserInterface
{
public:
    UserInterface(const Player& player);

    void Update(float deltaTime);
    void Draw();
        
    
private:
    const Player& rPlayer;
    std::vector<ManualRenderer> renderers;

    const SDL_Color bkgColour = {0,0,0,100};
    const SDL_Color dangerColour = {80,0,0,180};
    const SDL_Color seedColour = {16, 219,54, 200};
    const SDL_Color petalColour = {80, 15, 200,200};
    const SDL_Color sunColour = {240, 250, 0, 200};
    
    float maxBarWidth;
    float barWidth;

    // The vector index for the cooldown bar
    short cooldownIndex;
    
    // The vector index for the ammo bar
    short ammoIndex;

    // The vector index for the first heart (to get the rest... + 1 / 2)
    short fullHeartIndex;
    short emptyHeartIndex;
    
    void CreateUI();
    void CheckPlayerState();

    void UpdateBar();
};
