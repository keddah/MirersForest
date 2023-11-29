#include "Player.h"

Player::Player(std::vector<Tile>& floorRef): floor(floorRef)
{
}

void Player::Update(float deltaTime)
{
    controller.Update();
    
    // Reset velocity at the start of each frame so that it doesn't infinitely increase.
    velocity = Vector2();

    // If the jump button is held... gravity is slightly less powerful
    // if the crouch button is being held... gravity is slightly dmore powerful
    ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
    Move();
    Collisions();
    
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

    // print("InPlayer: " << pos.x << ", " << pos.y << rect.w << ", " << rect.h)
}

void Player::Collisions()
{
    const Vector2 predictedPos = pos + Vector2(velocity.x - 1, velocity.y - 1);
    const auto predictedRect = SDL_Rect{predictedPos.x, predictedPos.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    grounded = false;
    blocked = false;

    for (auto& tile : floor)
    {
        // Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separetly.
        const SDL_Rect tileRect = SDL_Rect{ tile.GetRenderer().GetPosition().x, tile.GetRenderer().GetPosition().y, tile.GetRenderer().GetDrawSize().x, tile.GetRenderer().GetDrawSize().y};
        if (SDL_HasIntersection(&predictedRect, &tileRect))
        {
            velocity = Vector2();
            continue;
        }

        grounded = predictedRect.y + predictedRect.h + 10 >= tileRect.y;
    }
    
    
}

void Player::Move()
{
    if(controller.GetMoveInputs()[0]) Jump();
    if(controller.GetMoveInputs()[1]) Crouch();


    const bool left = controller.GetMoveInputs()[2];
    const bool right = controller.GetMoveInputs()[3];

    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = left? -1 : (right? 1: 0);

    velocity.x += (blocked? 0 : direction) * moveSpeed;
}

void Player::Jump()
{
    if (!grounded) return;

    velocity.y -= jumpForce;
}

void Player::Crouch()
{
}

