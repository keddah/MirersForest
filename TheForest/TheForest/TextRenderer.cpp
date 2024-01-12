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
//
// #include "Renderers.h"
//
// TextRenderer::TextRenderer(const std::string& filePath, std::string displayText, const short _fontSize, Vector2 pos) : text(std::move(displayText))
// {
//     imagePath = filePath;
//     fontSize = _fontSize;
//     
//     ManualRenderer::SetPosition(pos);
//
//     TTF_Font* font = TTF_OpenFont(imagePath.c_str(), fontSize);
//     
//     if(!font)
//     {
//         print("invalid font")
//         return;
//     }
//     
//     // Render text to surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), drawColour);
//     TTF_CloseFont(font);
//
//     if(!textSurface)
//     {
//         print("invalid surface")
//         return;
//     }
//     
//     // Create texture from surface
//     thingsToRender.emplace_back(SDL_CreateTextureFromSurface(renderer, textSurface));
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
//     TTF_Font* font = TTF_OpenFont(imagePath.c_str(), fontSize);
//     
//     if(!font)
//     {
//         print("invalid font")
//         return;
//     }
//     
//     // Update the existing texture with the new surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), drawColour);
//     TTF_CloseFont(font);
//
//     if(!textSurface)
//     {
//         print("invalid surface")
//         return;
//     }
//     
//     SDL_UpdateTexture(thingsToRender[renderIndex], NULL, textSurface->pixels, textSurface->pitch);
//     print(SDL_GetError())
//
//     size = Vector2(textSurface->w, textSurface->h);
//     SDL_FreeSurface(textSurface);
//     
//     sourceRect.w = size.x;
//     sourceRect.h = size.y;
// }
