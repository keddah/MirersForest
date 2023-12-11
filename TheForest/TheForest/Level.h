#pragma once
#include "Player.h"
#include "SlimeManager.h"
#include "TileManager.h"

class Level
{
public:
    Level(short lvlNum);

    void UpdateSlide(float deltaTime);
    void FixedUpdate(float deltaTime);
    void DrawSlide();
    
private:
    class Slide
    {
    public:
        Slide() = default;
        Slide(Level* lvl): level(*lvl) {}
        void Draw();

        const std::vector<ManualRenderer>& GetManualRenderer(){ return manuals; }
        const std::vector<SpriteRenderer>& GetSpriteRenderer(){ return sprites; }
        
        void AddManualRenderer(const ManualRenderer& rndrr){ manuals.push_back(rndrr); }
        void AddSpriteRenderer(const SpriteRenderer& rndrr){ sprites.push_back(rndrr); }
        
    private:
        const Level& level;
        
        std::vector<ManualRenderer> manuals = std::vector<ManualRenderer>();
        std::vector<SpriteRenderer> sprites = std::vector<SpriteRenderer>();
    };
    ManualRenderer bkg = ManualRenderer("Sprites/background.jpg", {0,0});

    std::vector<Slide> slides = std::vector<Slide>(); 
    short currentSlide = 0;
    
    TileManager tileManager;
    Player player = Player(tileManager, currentSlide);
    SlimeManager slimeManger = SlimeManager(player, tileManager.GetTiles());

    
};
