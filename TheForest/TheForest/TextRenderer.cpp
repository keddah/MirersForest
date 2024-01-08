/**************************************************************************************************************
* Text Renderer - Code
*
* The code file for the Text renderer class. Responsible for drawing text to the screen by loading a ttf font and creating a texture
* from it.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "GameSingletons.h"
#include "Renderers.h"

TextRenderer::TextRenderer(const std::string& filePath, std::string displayText, const short size, Vector2 pos) : text(std::move(displayText))
{
    fontPath = filePath;
    fontSize = size;

    ManualRenderer::SetPosition(pos);
    
    SetText(text);
}

void TextRenderer::SetText(const std::string& displayText)
{
    text = displayText;
    
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if(!font)
    {
        print("bad filePath - text")
        return;
    }

    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), drawColour);
    TTF_CloseFont(font);

    // If this isn't the first time setting the text...
    if(!thingsToRender.empty()) thingsToRender[0] = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage);
    else thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage));

    size = Vector2(textImage->w, textImage->h);

    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
    SDL_FreeSurface(textImage);
}
