#include "TileManager.h"

TileManager::TileManager()
{
    test.GetRenderer().SetFrameCount();
    test.GetRenderer().SetIsAnimated(false);
    tiles.push_back(test);
}

void TileManager::MakeTiles()
{
    for(int w = 0; w < 100; w++)
    {
        for(int h = 0; h < 20; h++)
        {
            
        }
        
    }
}
