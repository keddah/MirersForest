#include "TileManager.h"

TileManager::TileManager(const std::vector<Collision*>& otherColliders)
{
    Image tileImg = Image(tilePaths[0].c_str());
    
    Vector2 position = Vector2(1920, 200);
    for(int i = 0; i < 20; i++)
    {
        tiles.emplace_back(tileImg, otherColliders);
        tiles[i].SetPosition(position);
        tiles[i].GetCollider().SetDebugColour(SDL_Rect{0,255,64,1});
        tiles[i].GetCollider().GetRect();
        
        position.x -= Tile::tileSize + 5;
    }
}
