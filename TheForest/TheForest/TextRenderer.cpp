// /**************************************************************************************************************
// * Text Renderer - Code
// *
// * The code file for the Text renderer class. Responsible for drawing text to the screen by loading a ttf font and creating a texture
// * from it.
// *
// * Created by Dean Atkinson-Walker 2023
// ***************************************************************************************************************/

#include "Renderers.h"

TextRenderer::TextRenderer(const std::string& filePath, std::string displayText, const short fontsize, Vector2 pos) : text(std::move(displayText))
{
    imagePath = filePath;
    fontSize = fontsize;

    ManualRenderer::SetPosition(pos);
    
    SetText(text);
}

void TextRenderer::SetText(const std::string& displayText)
{
    text = displayText;

    // If there's already a texture, destroy it so that a new one can replace it.
    if(!thingsToRender.empty()) if(thingsToRender.front()) SDL_DestroyTexture(thingsToRender.front());
    
    TTF_Font* font = TTF_OpenFont(imagePath.c_str(), fontSize);

    if(!font)
    {
        print("bad filePath - text")
        return;
    }

    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), drawColour);
    TTF_CloseFont(font);
    
    // If this isn't the first time setting the text...
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textImage);
    
    if (!thingsToRender.empty()) thingsToRender[0] = tex;
    else thingsToRender.emplace_back(tex);

    size = Vector2(static_cast<float>(textImage->w), static_cast<float>(textImage->h));
    SDL_FreeSurface(textImage);

    sourceRect.w = static_cast<int>(size.x);
    sourceRect.h = static_cast<int>(size.y);
    
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
