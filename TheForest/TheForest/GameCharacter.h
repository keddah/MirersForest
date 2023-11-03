#pragma once

#include "SpriteRenderer.h"

class Character
{
public:
    Character();
    ~Character();

    void Update();
    void Draw();
    
    void GainHealth();
    void TakeDamge();
    void Death();
    
private:
    SpriteRenderer renderer;

    HealthManager health;

    SDL_Rect rect;
};