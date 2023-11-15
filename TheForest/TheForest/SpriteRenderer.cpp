#include "SpriteRenderer.h"
#include "GameSingletons.h"
#include<iostream>

#include "Controllers.h"
#include "CustomTimer.h"


SpriteRenderer::SpriteRenderer(const char* paths[], Vector2& pos) : renderPos(pos)
{
	AddSpriteSheet(paths[0]);
	// for (int i = 0; i < sizeof(paths); i++) AddSpriteSheet(paths[i]);

	const Vector2 size = GetSpriteSize();

	// Only setting the size of the destination rect since the position would be updated each frame...
	destinationRect.w = size.x;
	destinationRect.h = size.y;
}

SpriteRenderer::SpriteRenderer(SDL_Rect& rect)
{
	destinationRect = rect;
}

void SpriteRenderer::Animate()
{
	// Creating a local texture each frame using the textures that were created in the constructor 
	const auto tex = Image(spriteImages[activeAnim].GetImagePath());
	const Vector2 frameSize = GetSpriteSize();

	// (x,y) the start position is the size of one of the frames * the frame number
	sourceRect = SDL_Rect{ frameSize.x * currentFrame, 0, frameSize.x, frameSize.y };
	destinationRect.x = renderPos.x;
	destinationRect.y = renderPos.y;
	
	// print("destination rect: (" << destinationRect.x << ", " << destinationRect.y << ", " << destinationRect.w << ", " << destinationRect.h << ")\n")

	// print("(" << renderPos.x << ", " << renderPos.y << ")\n")

	// The destination rect's position is already being set from the MoveSprite function
	SDL_RenderCopy(GameWindow::GetRenderer(), tex.GetTexture(), &sourceRect, &destinationRect);

	
	frameTimer += Time::GetDeltaTime() * 50;
	if (frameTimer > animSpeed)
	{
		currentFrame++;
		frameTimer = 0;
	}

	if (currentFrame > spriteImages[activeAnim].GetSpriteSheet().FrameCount() - 1) currentFrame = 0;
}

void SpriteRenderer::SetSpritePosition(const Vector2& newPos)
{
	renderPos = newPos;
	// print("renderPos: (" << renderPos.x << ", " << renderPos.y << ")\n")
}

Vector2 SpriteRenderer::GetSpriteSize()
{
	const Vector2 size = Vector2(
		spriteImages[activeAnim].GetSpriteSheet().Size().x / spriteImages[activeAnim].GetSpriteSheet().FrameCount(),
		spriteImages[activeAnim].GetSpriteSheet().Size().y
		);
	
	return size;
}

void SpriteRenderer::AddSpriteSheet(const char* path)
{
	// Creates a new Image object and adds it to the list of images
	spriteImages.emplace_back(path);
}

void SpriteRenderer::SetFrameCount(short frames)
{
	spriteImages[activeAnim].SetSpriteCount(frames);
}

void SpriteRenderer::ChangeSourceRect(SDL_Rect newRect)
{
	// sourceRect = SDL_Rect(newRect);
}

void SpriteRenderer::ChangeDestRect(SDL_Rect newRect)
{
	destinationRect = SDL_Rect(newRect);
}

void SpriteRenderer::Configure(const char* paths[], short frameCount)
{
	// Get rid of all of the existing textures
	spriteImages.clear();

	for(int i = 0; i < sizeof(paths); i++)
	{
		AddSpriteSheet(paths[i]);
	}

	SetFrameCount(frameCount);
}

void SpriteRenderer::FillRectangle(const int r, const int g, const int b, const int a)
{
	fillOn = true;
	fillColour = SDL_Rect{r,g,b,a};

	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), fillColour.x, fillColour.y, fillColour.w, fillColour.h);
	SDL_RenderFillRect(GameWindow::GetRenderer(), &destinationRect);
}

void SpriteRenderer::FillRectangle(SDL_Rect& colour)
{
	fillOn = true;
	fillColour = colour;

	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), fillColour.x, fillColour.y, fillColour.w, fillColour.h);
	SDL_RenderFillRect(GameWindow::GetRenderer(), &destinationRect);
}

void SpriteRenderer::UnfillRectangle()
{
	fillOn = false;
	fillColour = SDL_Rect();
}



