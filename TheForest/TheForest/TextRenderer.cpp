#include "GameSingletons.h"
#include "Renderers.h"

TextRenderer::TextRenderer(const std::string& filePath, const std::string& displayText, const short size, Vector2 pos) : text(displayText)
{
    fontPath = filePath;
    fontSize = size;
    txtPos = pos;
    SetPosition(txtPos);
    
    SetText(text);
}

void TextRenderer::Draw(bool referenced)
{
    if(!thingsToRender[0]) print("Can't render from this index")
    
    // Responsible for drawing the texture
    SDL_RenderCopyF(GameWindow::GetRenderer(), thingsToRender[0], &sourceRect, &drawRect);
}

void TextRenderer::SetText(const std::string& displayText)
{
    const int success = TTF_Init();
    if(success != 0)
    {
        print("failed init")
        return;
    }
    
    TTF_Font* txt = TTF_OpenFont(fontPath.c_str(), fontSize);

    if(!txt)
    {
        print("bad filePath")
        return;
    }

    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(txt, text.c_str(), drawColour);
    TTF_CloseFont(txt);

    size = Vector2(textImage->w, textImage->h);
    drawRect.x = txtPos.x;
    drawRect.y = txtPos.y;

    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
    SDL_FreeSurface(textImage);
}
