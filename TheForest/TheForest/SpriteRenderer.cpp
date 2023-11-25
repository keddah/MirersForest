#include "SpriteRenderer.h"
#include "GameSingletons.h"
#include "CustomTimer.h"


SpriteRenderer::SpriteRenderer(const SDL_FRect& rect, bool animated) : destinationRect(rect)
{
	isAnimated = animated;
	SetFrameCount(frameCount);
}

void SpriteRenderer::Draw()
{
	// Creating a local texture each frame using the textures that were created in the constructor 
	const Vector2 frameSize = GetSpriteSize();

	// (x,y) the start position is the size of one of the frames * the frame number
	sourceRect = SDL_Rect{ static_cast<int>(frameSize.x) * currentFrame, 0, static_cast<int>(frameSize.x), static_cast<int>(frameSize.y) };
	
	// The destination rect's position is already being set from the MoveSprite function
	SDL_RenderCopyF(GameWindow::GetRenderer(), spriteImages[activeAnim].GetTexture(), &sourceRect, &destinationRect);

	if(!isAnimated) return;
	
	frameTimer += Time::GetDeltaTime() * 50;
	if (frameTimer > animSpeed)
	{
		currentFrame++;
		frameTimer = 0;
	}

	if (currentFrame > spriteImages[activeAnim].GetSpriteSheet().FrameCount() - 1) currentFrame = 0;
}

Vector2 SpriteRenderer::GetSpriteSize()
{
	const Vector2 size = Vector2(
		spriteImages[activeAnim].GetSpriteSheet().Size().x / spriteImages[activeAnim].GetSpriteSheet().FrameCount(),
		spriteImages[activeAnim].GetSpriteSheet().Size().y
		);
	
	return size;
}

void SpriteRenderer::SetFrameCount(short frames)
{
	if(spriteImages.size() > 0) spriteImages[activeAnim].SetSpriteCount(frames);
}

void SpriteRenderer::SetSourceRect(const SDL_Rect newRect)
{
	sourceRect = SDL_Rect(newRect);
}

void SpriteRenderer::SetSprite(const std::string& path)
{
	spriteImages.clear();
	spriteImages.emplace_back(path.c_str());
}

void SpriteRenderer::SetImage(const Image& newImage)
{
	spriteImages.clear();

	spriteImages.push_back(newImage);
}

void SpriteRenderer::SetSpriteSheets(const std::vector<std::string>& paths)
{
	if(!spriteImages.empty()) spriteImages.clear();

	for (auto& path: paths) spriteImages.emplace_back(path.c_str());
}

void SpriteRenderer::FillRectangle(const int r, const int g, const int b, const int a)
{
	fillOn = true;
	fillColour = SDL_Rect{r,g,b,a};

	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), fillColour.x, fillColour.y, fillColour.w, fillColour.h);
	SDL_RenderFillRectF(GameWindow::GetRenderer(), &destinationRect);
}

void SpriteRenderer::FillRectangle(const SDL_Rect& colour)
{
	fillOn = true;
	fillColour = colour;

	SDL_SetRenderDrawColor(GameWindow::GetRenderer(), fillColour.x, fillColour.y, fillColour.w, fillColour.h);
	SDL_RenderFillRectF(GameWindow::GetRenderer(), &destinationRect);
}

void SpriteRenderer::UnFillRectangle()
{
	fillOn = false;
	fillColour = SDL_Rect();
}



