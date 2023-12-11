#include "GameSingletons.h"
#include "Player.h"

Player::Camera::Camera(Player* pP): rP(*pP)
{
}

void Player::Camera::Update() const
{
    // To stop the player from falling through the floor whenever they go to a new slide.
    
    if(rP.position.x > rP.screenWidth)
    {
        rP.levelSlide++;
        rP.position.x = rP.velocity.x;
    }
    
    else if(rP.levelSlide > 0 && rP.position.x < 0)
    {
        rP.levelSlide--;
        rP.position.x = rP.screenWidth + rP.velocity.x;
    }

    rP.tileManager.SetLevelSlide(rP.levelSlide);
}
