#pragma once


class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update();

	bool* GetInputs();

private:

	// Up .. Down .. Left .. Right
	bool moveInputs[4];
	void ReadInputs();
};