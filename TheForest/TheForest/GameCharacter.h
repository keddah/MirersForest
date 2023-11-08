#pragma once

#include "HealthManager.h" // final
#include "SpriteRenderer.h" //ok

class SpriteRenderer;

class Character
{
public:
    Character();
    ~Character();

    void Draw();

    void GainHealth();
    void TakeDamge(float intensity);
    void Death();


protected:
    HealthManager health = HealthManager();
    SDL_Rect rect;
    
private:
    SpriteRenderer renderer;


};