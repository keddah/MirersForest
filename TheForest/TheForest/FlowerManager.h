#pragma once
#include "Player.h"
#include "Vector2.h"

class FlowerManager
{
public:
    FlowerManager(Player& player);
    void Update(float deltaTime);
    void Draw();
    void SetLevelSlide(short slide);

    void SpawnFlowers(short lvlIndex);
    void Reset();
    
private:
    class FlowerUp
    {
    public:
        FlowerUp() = default;
        FlowerUp(Player& player, Vector2 pos);

        void Update(float deltaTime);
        void Draw() { if(!used) renderer.Draw(); }

        
        void SetPosition(Vector2 pos) { position = pos; renderer.SetPosition(position); }
        Vector2 GetPosition() const { return position; }

        short GetLevelSlide() const { return levelSlide; }
        void Reset() { used = false; respawnTimer = 0;}
    
    private:
        Vector2 position;
        Player& rP;
        ManualRenderer renderer = ManualRenderer("Sprites/flowerUp.png", position);
        SDL_FRect rect;

        short levelSlide;
    
        void Interaction();
        void Respawn(float deltaTime);
        
        bool used;

        const short respawnDelay = 20;
        float respawnTimer;
    };


    Player& rPlayer;
    
    std::vector<FlowerUp> flowers = std::vector<FlowerUp>();
    
    short levelSlide;
    
    void Level1Flowers();
};

