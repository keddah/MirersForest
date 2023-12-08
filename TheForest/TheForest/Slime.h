#pragma once
#include "Player.h"

class Slime: public Physics
{
public:
    Slime(Player& plyr, std::vector<Tile>& floorRef);
    ~Slime() = default;

    void Update(float deltaTime);

    void Collisions();
    void MoveTimer();
    void Patrol(float deltaTime);
    void NextPoint();

    void Death();
    
    const SpriteRenderer& GetRenderer() { return renderer; }

private:
    const std::vector<std::string> slimeSheets {"Sprites/Slimes/SlimeSheet.png", "Sprites/Slimes/movingSlime.png"};
    SpriteRenderer renderer = SpriteRenderer(slimeSheets, position);

    std::vector<Tile>& tiles; 
    Player& player;

    SDL_FRect rect;
    
    bool canMove;

    const float moveSpeed = .01f;
    const float waitTime = 7.5f;
    float patrolTimer = 0;
    Vector2 patrolPoints[2] {Vector2(900, 700), Vector2(100, 800)};
    short patrolIndex;
    
    void HitPlayer();
    void UpdateRectangle();
};
