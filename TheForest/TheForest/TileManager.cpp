#include "TileManager.h"

TileManager::TileManager(const std::vector<Collision>& otherColliders)
{
    Image tileImg = Image(tilePath.c_str());
    tileImg.SetSpriteCount();
    
    for(int w = 0; w < levelWidth; w++)
    {
        for(int h = 0; h < levelHeight; h++)
        {

            SDL_Rect sourceRect;
            sourceRect.x = (tileMap[w][h] % 6) * tileSize;
            sourceRect.y = (tileMap[w][h] / 6) * tileSize;
            sourceRect.w = tileImg.GetSpriteSheet().Size().x;
            sourceRect.h = tileImg.GetSpriteSheet().Size().y;

            SDL_FRect destinationRect;
            destinationRect.x = h * 512;
            destinationRect.y = w * 512;
            destinationRect.w = tileImg.GetSpriteSheet().Size().x;
            destinationRect.h = tileImg.GetSpriteSheet().Size().y;
            
            auto newCollision = Collision(otherColliders, 0,0,0,0);
            newCollision.GetRenderer().SetImage(tileImg);
            auto tile = Tile(newCollision);
            
            tile.SetDestRect(destinationRect);
            // tile.SetSourceRect(sourceRect);
            
            tiles.push_back(tile);
            print("h  " << h)
            }
        print("w  " << w)
    }
}
