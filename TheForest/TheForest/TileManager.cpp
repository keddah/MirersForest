#include "TileManager.h"

TileManager::TileManager(const std::vector<Collision>& otherColliders)
{
    Image tileImg = Image(tilePath.c_str());
    tileImg.SetSpriteCount();
    
    for(int w = 0; w < levelWidth; w++)
    {
        for(int h = 0; h < levelHeight; h++)
        {
            Tile tile = Tile(tileImg, otherColliders);

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
            
            tile.SetDestRect(destinationRect);
            tile.SetSourceRect(sourceRect);
            
            tiles.push_back(tile);
            print("h  " << h)
            }
        print("w  " << w)
    }
}
