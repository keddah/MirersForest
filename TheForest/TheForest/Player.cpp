#include "Player.h"

void Player::Update(float deltaTime)
{
    // Reset velocity at the start of each frame so that it doesn't infinitely increase.
    velocity = Vector2();
    
    ApplyGravity();

    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    pos += velocity;
    UpdateRectangle();
}

void Player::Init()
{
    if(initialised) return;

    renderer.SetIsAnimated();
    
    initialised = true;
}

// The player is only responsible for setting the position.
// The renderer is only responsible for setting the size.
// Together, they make the rectangle.
void Player::UpdateRectangle()
{
    const Vector2 playerSize = renderer.GetDrawSize();

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;

    print("InPlayer: " << pos.x << ", " << pos.y << rect.w << ", " << rect.h)
}

void Player::Move()
{
    // if(controller.GetMoveInputs()[0])
    // if(controller.GetMoveInputs()[0])
    // if(controller.GetMoveInputs()[0])
    // if(controller.GetMoveInputs()[0])
}

void Player::Jump()
{
}

