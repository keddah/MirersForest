#include "Player.h"

Player::Player(std::vector<Tile>& floorRef): floor(floorRef)
{
}

void Player::Update(float deltaTime)
{
    controller.Update();
    
    // Reset velocity at the start of each frame so that it doesn't infinitely increase.
    //velocity.x = velocity.x > maxSpeed ? maxSpeed: velocity.x;
    //velocity.y = velocity.y > maxSpeed ? maxSpeed: velocity.y;

    // If the jump button is held... gravity is slightly less powerful
    // if the crouch button is being held... gravity is slightly dmore powerful
    ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
   
    // Move has to be called first so that collisions can negate its newly added velocity.
    Move();
    Collisions();
    
    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    pos += velocity;
    velocity = Vector2();
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
}

void Player::Collisions()
{
    const Vector2 predictedPosX = pos + Vector2(velocity.x, 0);
    const Vector2 predictedPosY = pos + Vector2(0, velocity.y);
    const auto predictedRectX = SDL_FRect{ predictedPosX.x, predictedPosX.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y };
    const auto predictedRectY = SDL_FRect{predictedPosY.x, predictedPosY.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    grounded = false;

    for (auto& tile : floor)
    {
        // Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separetly.
        const SDL_FRect tileRect = SDL_FRect{ tile.GetRenderer().GetPosition().x, tile.GetRenderer().GetPosition().y, tile.GetRenderer().GetDrawSize().x, tile.GetRenderer().GetDrawSize().y};
        
        // Separate the axis collisions.
        const bool predictedCollisionX = SDL_HasIntersectionF(&predictedRectX, &tileRect);
        const bool predictedCollisionY = SDL_HasIntersectionF(&predictedRectY, &tileRect);

        if (predictedCollisionX)
        {
            velocity = Vector2(0, velocity.y);
        }
        if (predictedCollisionY)
        {
            velocity = Vector2(velocity.x, 0);
            grounded = true;
        }

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

    velocity.x += direction * moveSpeed;
}

void Player::Jump()
{
    if (!grounded) return;

    velocity.y -= jumpForce;
}

void Player::Crouch()
{
}

