#include "Player.h"

Player::Player()
{
}

void Player::Update(float deltaTime)
{
    renderer->UpdatePosition(pos);
    UpdateRectangle();
}

void Player::Init()
{
    if(initialised) return;

    renderer = new SpriteRenderer(spritePath, true);
    renderer->SetIsAnimated();
    
    initialised = true;
}

// The player is only responsible for setting the position.
// The renderer is only responsible for setting the size.
// Together, they make the rectangle.
void Player::UpdateRectangle()
{
    const Vector2 playerSize = renderer->GetDrawSize();

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;
}

