#pragma once

#include "HealthManager.h"
#include "SpriteRenderer.h"

class Character
{
public:
    Character();
    ~Character();

    void GainHealth();
    void TakeDamge(float intensity);
    void Death();


protected:
    HealthManager health = HealthManager();
    SDL_Rect rect;
    
private:
    SpriteRenderer renderer;


};