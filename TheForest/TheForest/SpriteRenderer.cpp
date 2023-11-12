#include "SpriteRenderer.h"
#include "GameSingletons.h"
#include<iostream>

#include "Controllers.h"
#include "CustomTimer.h"

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::SpriteRenderer(const char* paths[])
{
	AddSpriteSheet(paths[0]);
	// for (int i = 0; i < sizeof(paths); i++) AddSpriteSheet(paths[i]);

	const Vector2 size = Vector2(spriteImages[activeAnim].GetSpriteSheet().Size().x/4, spriteImages[activeAnim].GetSpriteSheet().Size().y);

	// Only setting the size of the destination rect since the position would be updated each frame...
	destinationRect.w = size.x;
	destinationRect.h = size.y;
}


void SpriteRenderer::Animate()
{
	// Creating a local texture each frame using the textures that were created in the constructor 
	const auto tex = Image(spriteImages[activeAnim].GetImagePath());

	const short frameCount = spriteImages[activeAnim].GetSpriteSheet().FrameCount();
	const Vector2 frameSize = Vector2(spriteImages[activeAnim].GetSpriteSheet().Size().x / frameCount, spriteImages[activeAnim].GetSpriteSheet().Size().y);

	// (x,y) the start position is the size of one of the frames * the frame number
	sourceRect = SDL_Rect{ frameSize.x * currentFrame, 0, frameSize.x, frameSize.y };
	destinationRect.x = renderPos.x;
	destinationRect.y = renderPos.y;
	
	print("destination rect: (" << destinationRect.x << ", " << destinationRect.y << ", " << destinationRect.w << ", " << destinationRect.h << ")\n")
	
	
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
	print("renderPos: (" << renderPos.x << ", " << renderPos.y << ")\n")
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

void SpriteRenderer::Configure(const char* paths[], SDL_Rect source, SDL_Rect destination)
{
	// Get rid of all of the existing textures
	spriteImages.clear();

	for(int i = 0; i < sizeof(paths); i++)
	{
		AddSpriteSheet(paths[i]);
	}

	sourceRect = SDL_Rect(source);
	destinationRect = SDL_Rect(destination);
}


