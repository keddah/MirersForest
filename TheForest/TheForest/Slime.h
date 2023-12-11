#pragma once
#include "Player.h"

class Slime: public Physics
{
public:
    Slime(Player& plyr, std::vector<Tile>& floorRef);
    ~Slime() = default;

    void Update(float deltaTime);
    void Draw() { if(!dead) renderer.Draw(); }
    
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

    std::vector<Tile>& tiles; 
    Player& player;

    bool dead = false;
    
    SDL_FRect rect;

    bool canMove;

    const float moveSpeed = .01f;
    const float waitTime = 7.5f;
    float patrolTimer = 0;
    Vector2 patrolPoints[2] {Vector2(900, 700), Vector2(100, 800)};
    short patrolIndex;

    // The section of the level that this slime is present on
    short levelSlide;
    
    void Collisions();
    void MoveTimer();
    void Patrol(float deltaTime);
    void NextPoint();

    void Death();
    
    void HitPlayer() const;
    void UpdateRectangle();
};
