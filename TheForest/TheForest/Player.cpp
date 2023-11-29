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
    Collisions();
    Move();
    
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
    const Vector2 predictedPos = pos += velocity;

    const auto predictedRect = SDL_Rect{predictedPos.x, predictedPos.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    bool collision = false;
    
    for(auto& tile: floor)
    {
        const SpriteRenderer& tileRndrr = tile.GetRenderer();
        
        // Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separetly.
        SDL_Rect tileRect = SDL_Rect{ tileRndrr.GetPosition().x, tileRndrr.GetPosition().y, tileRndrr.GetDrawSize().x, tileRndrr.GetDrawSize().y};
        print("dest: " << predictedRect.x << ", " << predictedRect.y << ", " << predictedRect.w << ", " << predictedRect.h)

        if(SDL_HasIntersection(&predictedRect, &tileRect))
        {
            collision = true;
        }
    }

    //canMove = !collision; 
    print(collision)
}

void Player::Move()
{
    if(controller.GetMoveInputs()[0]) Jump();
    if(controller.GetMoveInputs()[1]) Crouch();

    const bool left = controller.GetMoveInputs()[2];
    const bool right = controller.GetMoveInputs()[3];

    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = left? -1 : (right? 1: 0);

    velocity.x += direction * moveSpeed;
}

void Player::Jump()
{
    
    velocity.y -= jumpForce;
}

void Player::Crouch()
{
}

