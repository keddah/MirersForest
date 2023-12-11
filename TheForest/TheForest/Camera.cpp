#include "GameSingletons.h"
#include "Player.h"

Player::Camera::Camera(Player* plyr): thisPlayer(*plyr)
{
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, &screenHeight);
}

void Player::Camera::Update()
{
    if(thisPlayer.position.x > screenWidth)
    {
        slide++;
        thisPlayer.position.x = thisPlayer.velocity.x;
        thisPlayer.tileManager.NextSlide();
    }

    else if(slide > 0 && thisPlayer.position.x < 0)
    {
        slide--;
        thisPlayer.position.x = thisPlayer.velocity.x;
        thisPlayer.tileManager.PreviousSlide();
    }
}