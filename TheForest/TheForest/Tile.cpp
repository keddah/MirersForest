#include "TileManager.h"

Tile::Tile(const std::string& path, const std::vector<Collision*>& _otherColliders): otherColliders(_otherColliders), renderer(collider.GetRenderer())
{
    renderer.SetFrameCount();
    renderer.SetSprite(path);
}

Tile::Tile(const Image& image, const std::vector<Collision*>& _otherColliders): otherColliders(_otherColliders), renderer(collider.GetRenderer())
{
    renderer.SetFrameCount();
    renderer.SetImage(image);
}


/////// Edit destination rectangle
void Tile::SetDestRect(SDL_FRect newRect)
{
    collider.SetRect(newRect);
}

void Tile::SetDestRect(Vector2 position, Vector2 dimensions)
{
    collider.SetRect(position, dimensions);
}

void Tile::SetDestRect(Vector2 position, float width, float height)
{
    collider.SetRect(position, width, height);
}

void Tile::SetDestRect(float x, float y, Vector2 dimensions)
{
    collider.SetRect(x, y, dimensions);
}

void Tile::SetDestRect(float x, float y, float width, float height)
{
    collider.SetRect(x, y, width, height);
}



/////// Edit source rectangle
void Tile::SetSourceRect(SDL_Rect newRect)
{
    
    collider.GetRenderer().SetSourceRect(newRect);
}

void Tile::SetSourceRect(Vector2 position, Vector2 dimensions)
{
    collider.GetRenderer().SetSourceRect(SDL_Rect{static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(dimensions.x), static_cast<int>(dimensions.y)});
}

void Tile::SetSourceRect(Vector2 position, int width, int height)
{
    collider.GetRenderer().SetSourceRect(SDL_Rect{static_cast<int>(position.x), static_cast<int>(position.y), width, height});
}

void Tile::SetSourceRect(int x, int y, Vector2 dimensions)
{
    collider.GetRenderer().SetSourceRect(SDL_Rect{x, y, static_cast<int>(dimensions.x), static_cast<int>(dimensions.y)});
}

void Tile::SetSourceRect(int x, int y, int width, int height)
{
    collider.GetRenderer().SetSourceRect(SDL_Rect{x, y, width, height});
}
