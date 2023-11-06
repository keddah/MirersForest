#pragma once


class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update();
	
	bool* GetMoveInputs();
	bool IsLMB() const;
	bool IsRMB() const;

private:
	bool lmb;
	bool rmb;

	void ClearInputs();
	
	// Up .. Down .. Left .. Right
	bool moveInputs[4];
	void ReadInputs();
};