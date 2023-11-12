#include "SpriteRenderer.h"

SpriteSheet::SpriteSheet(Vector2 size, short count)
{
	imageSize = size;
	frameCount = count;
}

SpriteSheet::SpriteSheet()
{
}

void SpriteSheet::SetFrameCount(short count)
{
	frameCount = count;
}

void SpriteSheet::SetImageSize(const Vector2& size)
{
	imageSize = size;
}

void SpriteSheet::SetImageSize(const int x, const int y)
{
	imageSize.x = x;
	imageSize.y = y;
}
