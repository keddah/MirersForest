#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 pos, SDL_Rect source, int tileSize);

    const ManualRenderer& GetRenderer() const { return renderer; }
    void Draw() { renderer.Draw(levelSlide); }
    void Reset();
    
    // void Scroll(short slide);

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2 pos) { position = pos; renderer.SetPosition(pos); }
    
    short GetLevelSlide() const { return levelSlide; }
    void SetSlide(const short slide) { levelSlide = slide; }
    
private:
    std::string spritePath;
    Vector2 position;
    ManualRenderer renderer;

    SDL_Rect sourceRect;
    int size;
        
    
    short levelSlide;
};
