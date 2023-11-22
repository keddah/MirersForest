#include "SpriteRenderer.h"
#include "CustomTimer.h"



SpriteRenderer::SpriteRenderer(const std::vector<std::string>& paths, const SDL_FRect& rect): destinationRect(rect)
{
	// Creates a new Image object and adds it to the list of images
	for (auto& path: paths) spriteImages.emplace_back((path.c_str()));
}

SpriteRenderer::SpriteRenderer(const SDL_FRect& rect) : destinationRect(rect)
{

}

void SpriteRenderer::Animate()
{
	// Creating a local texture each frame using the textures that were created in the constructor 
	const Vector2 frameSize = GetSpriteSize();

	// (x,y) the start position is the size of one of the frames * the frame number
	sourceRect = SDL_Rect{ static_cast<int>(frameSize.x) * currentFrame, 0, static_cast<int>(frameSize.x), static_cast<int>(frameSize.y) };
	
	print("renderer: (" << destinationRect.x << ", " << destinationRect.y << ", " << destinationRect.w << ", " << destinationRect.h << ")\n")

	// The destination rect's position is already being set from the MoveSprite function
	SDL_RenderCopyF(GameWindow::GetRenderer(), spriteImages[activeAnim].GetTexture(), &sourceRect, &destinationRect);
	
	
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
	//renderPos = newPos;
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

void SpriteRenderer::SetFrameCount(short frames)
{
	spriteImages[activeAnim].SetSpriteCount(frames);
}

void SpriteRenderer::SetSourceRect(const SDL_Rect newRect)
{
	sourceRect = SDL_Rect(newRect);
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

void SpriteRenderer::UnfillRectangle()
{
	fillOn = false;
	fillColour = SDL_Rect();
}



