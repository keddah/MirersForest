// /**************************************************************************************************************
// * Text Renderer - Code
// *
// * The code file for the Text renderer class. Responsible for drawing text to the screen by loading a ttf font and creating a texture
// * from it.
// *
// * Created by Dean Atkinson-Walker 2023
// ***************************************************************************************************************/

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
    if(!thingsToRender.empty()) if(thingsToRender.front()) SDL_DestroyTexture(thingsToRender.front());
    
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if(!font)
    {
        print("bad filePath - text")
        return;
    }

    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), drawColour);

    // If this isn't the first time setting the text...
    if(!thingsToRender.empty()) thingsToRender[0] = SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage);
    else thingsToRender.push_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textImage));

    size = Vector2(textImage->w, textImage->h);
    SDL_FreeSurface(textImage);

    sourceRect.w = size.x;
    sourceRect.h = size.y;
    
}


/**************************************************************************************************************
* Text Renderer - Code
*
* The code file for the Text renderer class. Responsible for drawing text to the screen by loading a ttf font and creating a texture
* from it.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

// #include "GameSingletons.h"
// #include "Renderers.h"
//
// TextRenderer::TextRenderer(const std::string& filePath, std::string displayText, const short _fontSize, Vector2 pos) : text(std::move(displayText))
// {
//     fontPath = filePath;
//     fontSize = _fontSize;
//     
//     ManualRenderer::SetPosition(pos);
//
//     font = TTF_OpenFont(fontPath.c_str(), fontSize);
//     
//     // Render text to surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), drawColour);
//     
//     // Create texture from surface
//     thingsToRender.emplace_back(SDL_CreateTextureFromSurface(GameWindow::GetRenderer(), textSurface));
//     
//     size = Vector2(textSurface->w, textSurface->h);
//     SDL_FreeSurface(textSurface);
//     
//     sourceRect.w = size.x;
//     sourceRect.h = size.y;
// }
//
// void TextRenderer::SetText(const std::string& displayText)
// {
//     text = displayText;
//
//     if(!font)
//     {
//         print("invalid font")
//         return;
//     }
//     
//     // Update the existing texture with the new surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), drawColour);
//
//     SDL_UpdateTexture(thingsToRender.front(), NULL, textSurface->pixels, textSurface->pitch);
//
//     size = Vector2(textSurface->w, textSurface->h);
//     SDL_FreeSurface(textSurface);
//
//     sourceRect.w = size.x;
//     sourceRect.h = size.y;
//     
// }
