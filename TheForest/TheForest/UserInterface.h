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
    std::vector<TextRenderer> txtRenderers;

    const short timeSize = 120;
    TextRenderer timeTxt = TextRenderer("Fonts/Oxygen-Regular.ttf", "undertheweather", timeSize, {100,100});

    // const short projectileTxtSize = 10;
    // const TTF_Font* projectileTxt = TTF_OpenFont("Fonts/Quicksand-Regular.ttf", projectileTxtSize); 
    
    const SDL_Color bkgColour = {0,0,0,100};
    const SDL_Color dangerColour = {80,0,0,180};
    const SDL_Color seedColour = {16, 219,54, 200};
    const SDL_Color petalColour = {80, 15, 200,200};
    const SDL_Color sunColour = {240, 250, 0, 200};
    
    float maxBarWidth;
    float barWidth;

    // The vector index for the heart background
    short heartBkgIndex;
    
    // The vector index for the cooldown bar
    short cooldownIndex;
    
    // The vector index for the ammo bar
    short ammoIndex;

    // The vector index for the first heart (to get the rest... + 1 / 2)
    short fullHeartIndex;
    short emptyHeartIndex;

    float seconds;
    int minutes;
    
    void CreateUI();
    void CheckPlayerState();

    void UpdateBar();

    void LevelTime(float deltaTime);
};
