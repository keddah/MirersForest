#pragma once
#include "Collider.h"

class Tile
{
    public:
    Tile() = default;    
    Tile(const Collision& _collider);    

    Collision& GetCollider() { return collider; }

    void SetSourceRect(SDL_Rect newRect);
    void SetSourceRect(Vector2 position, Vector2 dimensions);
    void SetSourceRect(int x, int y, int width, int height);
    void SetSourceRect(int x, int y, Vector2 dimensions);
    void SetSourceRect(Vector2 position, int width, int height);
    
    void SetDestRect(SDL_FRect newRect);
    void SetDestRect(Vector2 position, Vector2 dimensions);
    void SetDestRect(Vector2 position, float width, float height);
    void SetDestRect(float x, float y, Vector2 dimensions);
    void SetDestRect(float x, float y, float width, float height); 
    
    void SetPosition(Vector2 pos) { collider.SetPosition(pos); } 
    void SetPosition(float x, float y) { collider.SetPosition(x,y); }

    // Doesn't have to be a vector since every tile will be a square.
    
    private:
    Collision collider;
};


class TileManager
{
public:
    TileManager(const std::vector<Collision>& _otherColliders);

    std::vector<Tile>& GetTiles() { return tiles; }
    
private:
    // Creating a matrix for the tilemap
    static constexpr short levelWidth = 100;
    static constexpr short levelHeight = 10;
    short tileMap[levelWidth][levelHeight];
    static constexpr short tileSize = 16;
    
    std::vector<Tile> tiles = std::vector<Tile>();
    std::string tilePath {"Sprites/test16-16.jpg"};
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
