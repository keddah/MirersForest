/**************************************************************************************************************
* Flower Manager - Header
*
* The header file for the Flower manager class. Responsible for creating object references that each flower will need
* in order to be created. Also creates functions that handle the creation / management of flowers.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include "Player.h"
#include "Vector2.h"

class FlowerManager
{
public:
    FlowerManager(Player& player);
    ~FlowerManager()
    {
        for(auto& flower: flowers) flower.Destroy();
        flowers.clear();
    }

    void FixedUpdate(float deltaTime);
    void Draw();
    void SetLevelSlide(short slide);

    void SpawnFlowers(short lvlIndex, bool reset = false);
    void Reset();
    
private:
    class FlowerUp
    {
    public:
        FlowerUp() = default;
        FlowerUp(Player& player, Vector2 pos);
        
        void Update(float deltaTime);
        void Draw() { if(!used) renderer.Draw(); }
        void Destroy() { renderer.DestroyAllTextures(); }

        
        void SetPosition(Vector2 pos) { position = pos; renderer.SetPosition(position); }
        Vector2 GetPosition() const { return position; }

        short GetLevelSlide() const { return levelSlide; }
        void SetSlide(const short slide) { levelSlide = slide; }
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
    
    short levelSlide = 0;
    
    void Level1Flowers();
    void Level2Flowers();
};

