#include "TileManager.h"

Tile::Tile(const std::string& path, const std::vector<Collision*>& _otherColliders): otherColliders(_otherColliders), renderer(collider.GetRenderer())
{
    renderer.SetFrameCount();
    renderer.SetSprite(path);
}

Tile::Tile(Image image, const std::vector<Collision*>& _otherColliders): otherColliders(_otherColliders), renderer(collider.GetRenderer())
{
    
}