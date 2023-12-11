#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize);

    const ManualRenderer& GetRenderer() const { return renderer; }
    void Draw() { renderer.Draw(levelSlide); }
    
    // void Scroll(short slide);

    const Vector2& GetPosition() const { return pos; }
    
    short GetLevelSlide() const { return levelSlide; }
    void SetSlide(const short slide) { levelSlide = slide; }
    
private:
    std::string spritePath;
    Vector2 pos;
    ManualRenderer renderer;

    short levelSlide;
};
