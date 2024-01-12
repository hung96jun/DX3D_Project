#pragma once

#define MAX_INPUT_MOUSE 8

enum class MouseRotation : int
{
	NONE = 0,
	LEFT,
	RIGHT,
};

enum class ButtonInputState : int
{
	NONE = 0,
	DOWN,
	UP,
	PRESS,
	DBLCLK,
};

class Mouse
{
private:
	Mouse();
	~Mouse();

public:
	void SetHandle(HWND handle)
	{
		Handle = handle;
	}

	static Mouse* Get();

	static void Create();
	static void Delete();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);
	Vector3 GetPosition() { return Position; }

	bool IsDown(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::DOWN); }
	bool IsUp(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::UP); }
	bool IsPress(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::PRESS); }

	Vector3 GetWheelValue()
	{
		return WheelMoveValue;
	}

private:
	static Mouse* Instance;

	HWND Handle = nullptr;
	Vector3 Position;

	byte ButtonCurState[MAX_INPUT_MOUSE];
	byte ButtonBeforeState[MAX_INPUT_MOUSE];
	byte ButtonMap[MAX_INPUT_MOUSE];

	Vector3 WheelCurStatus;
	Vector3 WheelBeforeStatus;
	Vector3 WheelMoveValue;

	DWORD DoubleClickTime;
	DWORD StartDoubleClick[MAX_INPUT_MOUSE];
	int ButtonCount[MAX_INPUT_MOUSE];
};

