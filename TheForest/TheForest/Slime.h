/**************************************************************************************************************
* Slime - Header
*
* The header file for the Slime class. Responsible for creating the renderer for slime objects and creating functions that
* will be ran by the slime manager.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include "Player.h"

class Slime: public Physics
{
public:
    Slime(Player& plyr, std::vector<Tile>& floorRef, const AudioManager& sound);
    ~Slime() = default;

    void Update(float deltaTime);
    void Draw() { if(!dying) renderer.Draw(); }

    void DeathAnimation();
    
    void SetPatrol(const std::vector<Vector2>& points, float delay = 7.5f, float speed = .01f);
    
    const Vector2& GetPosition() const { return position; }
    void SetPosition(Vector2 pos) { position = pos; }
    void SetPosition(float x, float y) { position = {x, y}; }

    void SetSlide(const short slide) { levelSlide = slide; }
    short GetLevelSlide() const { return levelSlide; }
    
    bool IsDead() const { return dead; }
    
    const SpriteRenderer& GetRenderer() const { return renderer; }

private:
    const std::vector<std::string> slimeSheets {"Sprites/Slimes/SlimeSheet.png", "Sprites/Slimes/movingSlime.png"};
    SpriteRenderer renderer = SpriteRenderer(slimeSheets, position);
    Vector2 vfxPos = position;
    SpriteRenderer deathRenderer = SpriteRenderer("Sprites/Slimes/slimeDeath.png", vfxPos, true, false);

    std::vector<Tile>& rTiles; 
    Player& rPlayer;
    const AudioManager& rAudio;

    bool dead = false;
    bool dying = false;
    
    SDL_FRect rect;

    const short idleAnim = 0;
    const short moveAnim = 1;
    
    bool canMove;

    float moveSpeed = .01f;
    float waitTime = 7.5f;
    float patrolTimer = 0;
    std::vector<Vector2> patrolPoints;
    short patrolIndex;

    // The section of the level that this slime is present on
    short levelSlide;
    
    void Collisions();
    void Patrol(float deltaTime);
    void NextPoint();

    void Death();
    
    void HitPlayer() const;
    void UpdateRectangle();
};
