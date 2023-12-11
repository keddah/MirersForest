#include "GameSingletons.h"
#include "Player.h"

Player::Camera::Camera(Player* plyr): thisPlayer(*plyr)
{
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, nullptr);
}

void Player::Camera::Update() const
{
    if(thisPlayer.position.x > screenWidth)
    {
        thisPlayer.levelSlide++;
        thisPlayer.position.x = thisPlayer.velocity.x;
        thisPlayer.tileManager.NextSlide();
    }
    
    else if(thisPlayer.levelSlide > 0 && thisPlayer.position.x < 0)
    {
        thisPlayer.levelSlide--;
        thisPlayer.position.x = thisPlayer.velocity.x;
        thisPlayer.tileManager.PreviousSlide();
    }
}
