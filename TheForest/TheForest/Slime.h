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
    void Respawn();
    
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
