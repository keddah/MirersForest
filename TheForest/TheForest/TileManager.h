#pragma once
#include "Collider.h"

class Tile
{
    public:
    Tile() = default;    
    Tile(const std::string& path, const std::vector<Collision*>& _otherColliders);    
    Tile(Image image, const std::vector<Collision*>& _otherColliders);    
    Collision& GetCollider() { return collider; }
    void SetPosition(Vector2 pos) { collider.SetPosition(pos); } 
    void SetPosition(float x, float y) { collider.SetPosition(x,y); }

    // Doesn't have to be a vector since every tile will be a square.
    static constexpr float tileSize = 20;
    
    private:
    Collision collider = Collision(otherColliders, 0, 0, tileSize, tileSize);

    const std::vector<Collision*>& otherColliders;

    // Creating a reference so that its easier to get to (rather than calling GetRenderer each time)
    SpriteRenderer& renderer;
};


class TileManager
{
public:
    TileManager(const std::vector<Collision*>& _otherColliders);
    std::vector<Tile>& GetTiles() { return tiles; }
    
private:
    std::vector<Tile> tiles = std::vector<Tile>();
    std::vector<std::string> tilePaths {"Sprites/testTile.png"};
    enum ETileSheets
    {
        Empty = 0,
        Grass,
        Dirt,
        Stone,
        TreeBark,
        Leaves,
        Bush1,
        Bush2
    };
    SpriteSheet tileSpriteSheet;
};
