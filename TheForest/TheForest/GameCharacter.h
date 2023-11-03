#pragma once

#include "SpriteRenderer.h"
#include "HealthManager.h"

class Character
{
public:
    Character();
    ~Character();

    void Update();
    void Draw();
    
    void GainHealth();
    void TakeDamge(float intensity);
    void Death();


protected:
    HealthManager health = HealthManager();
    
private:
    SpriteRenderer renderer;


    SDL_Rect rect;
};