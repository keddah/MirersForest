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

    const std::string font_quicksand = "Fonts/Quicksand-Regular.ttf";
    const std::string font_oxygen = "Fonts/Oxygen-Regular.ttf";
    
    const short timeSize = 36;
    const short projTxtSize = 20;

    // Colours
    const SDL_Color bkgColour = {0,0,0,100};
    const SDL_Color dangerColour = {80,0,0,180};

    const SDL_Color seedBkgColour = {5,30,10, 100};
    const SDL_Color petalBkgColour = {17,10,30,100};
    const SDL_Color sunBkgColour = {35,35,10 , 100};
    
    const SDL_Color seedColour = {16, 219,54, 200};
    const SDL_Color petalColour = {80, 15, 200,200};
    const SDL_Color sunColour = {240, 250, 0, 200};
    
    float maxBarWidth;
    float barWidth;

    // The vector index for the heart background
    short heartBkgIndex;

    short projBkgIndex;
    
    // The vector index for the cooldown bar
    short cooldownIndex;
    
    // The vector index for the ammo bar
    short ammoIndex;

    // The vector index for the text of the selected projectile
    short projIndex;
    
    short timerIndex;

    // The vector index for the first heart (to get the rest... + 1 / 2)
    short fullHeartIndex;
    short emptyHeartIndex;

    float seconds;
    int minutes;

    // Needs to have an initial value
    std::string time = "f";
    std::string currentProj = "f";
    
    void CreateUI();
    void CheckPlayerState();

    void UpdateBar();

    void LevelTime(float deltaTime);
};
