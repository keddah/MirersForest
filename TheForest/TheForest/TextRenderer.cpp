#include "GameSingletons.h"
#include "Renderers.h"

TextRenderer::TextRenderer(const std::string& filePath, const std::string& displayText, const short size, Vector2 pos)
{
    fontPath = filePath;
    fontSize = size;
    txtPos = pos;
    
    SetText(displayText);
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

    text = displayText;
    
    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(txt, text.c_str(), drawColour);
    TTF_CloseFont(txt);

    // If this isn't the first time setting the text...
    if(!thingsToRender.empty()) thingsToRender[0] = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage);
    else thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage));

    size = Vector2(textImage->w, textImage->h);
    drawRect.x = txtPos.x;
    drawRect.y = txtPos.y;

    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
    SDL_FreeSurface(textImage);
}
