#pragma once
#include<iostream>


class SpriteSheet
{
public:
	SpriteSheet(Vector2 size, short count);
	SpriteSheet();

	// Set the number of frames there are in the spritesheet
	void SetFrameCount(short count);
	short FrameCount() const { return frameCount; }

	void SetImageSize(const Vector2& size);
	void SetImageSize(const int x, const int y);
	Vector2& Size() { return imageSize; }

	
private:
	short frameCount = 4;
	Vector2 imageSize;
};

