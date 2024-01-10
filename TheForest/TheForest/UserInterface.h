/**************************************************************************************************************
* User Interface - Header
*
* The header file for the UI class and the private class Button. This class is responsible for making UI elements based on the player's state.
* Also creates menus for when the player dies, pauses or finishes a level.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include "Player.h"
#include "Renderers.h"

class UserInterface
{
public:
    UserInterface(Player& player);
    
    void Update(float deltaTime);
    void Draw();
    void EndGame();
    
private:
    class Button
    {
    public:
        Button(SDL_Rect rect, SDL_Color colour);
        Button(int x, int y, int w, int h, SDL_Colour colour);

        void Draw() { renderer.Draw(); }
        void Hide() { renderer.SetVisibility(false); }
        void Show() { renderer.SetVisibility(true); }
        
        void SetPosition(Vector2 pos) { renderer.SetPosition(pos); }
        void SetSize(Vector2 size) { renderer.SetDrawSize(size); }
        void SetRect(SDL_Rect rect)
        {
            renderer.SetPosition(Vector2(rect.x, rect.y));
            renderer.SetDrawSize(Vector2(rect.w, rect.h));
        }
        const SDL_Rect& GetRect() const { return { static_cast<int>(renderer.GetRect().x), static_cast<int>(renderer.GetRect().y), static_cast<int>(renderer.GetRect().w), static_cast<int>(renderer.GetRect().h) }; }

    private:
        ManualRenderer renderer = ManualRenderer(Vector2(), Vector2());
    };


    
    Player& rPlayer;

    std::vector<Button> buttons;
    
    std::vector<ManualRenderer> renderers;
    std::vector<TextRenderer*> txtRenderers;

    const std::string font_quicksand = "Fonts/Quicksand-Regular.ttf";
    const std::string font_oxygen = "Fonts/Oxygen-Regular.ttf";

    ManualRenderer pauseScreen = ManualRenderer("Sprites/UI/pauseScreen.png", {});
    ManualRenderer deathScreen = ManualRenderer("Sprites/UI/deathscreen.png", {});
    ManualRenderer endScreen = ManualRenderer("Sprites/UI/endScreen.png", {});
    ManualRenderer completionScreen = ManualRenderer("Sprites/UI/levelCompletionSheet.png", {});
    void LevelCompletion();
    
    const short timeSize = 36;
    const short projTxtSize = 20;

    // Colours
    const SDL_Color bkgColour = {0,0,0,100};
    const SDL_Color dangerColour = {80,0,0,180};

    const SDL_Color seedBkgColour = {5,30,10, 100};
    const SDL_Color petalBkgColour = {17,10,30,100};
    const SDL_Color sunBkgColour = {35,35,10 , 100};
    
    const SDL_Color seedColour = {16, 219,54, 220};
    const SDL_Color petalColour = {80, 15, 200,220};
    const SDL_Color sunColour = {240, 250, 0, 220};
    
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

    // Timer that shows the death screen after it elapses.
    float deathDelayTimer;
    
    bool timerOn;
    float seconds;
    int minutes;

    // Needs to have an initial value
    std::string time = "0";
    std::string currentProjectile = "f";
    
    void CreateUI();
    void CheckPlayerState();
    void Respawning(float deltaTime);
    
    void UpdateBar();

    void LevelTime(float deltaTime);

    void ButtonPresses();

    void Pausing();
    void PressResume();
    void PressRestart();
    static void PressQuit();
};
