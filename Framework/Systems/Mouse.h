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
	static void Destroyt();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);
	Vector3 GetPosition() { return Position; }

	bool IsDown(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::DOWN); }
	bool IsUp(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::UP); }
	bool IsPress(DWORD button) { return ButtonMap[button] == static_cast<DWORD>(ButtonInputState::PRESS); }

	Vector3 GetMouseMoveValue()
	{
		return MouseMoveValue;
	}

	void SetMouseWheel(const int Delta) { WheelDelta = Delta; }
	const int GetMouseWheel() { return WheelDelta; }

private:
	static Mouse* Instance;

	HWND Handle = nullptr;
	Vector3 Position;

	byte ButtonCurState[MAX_INPUT_MOUSE];
	byte ButtonBeforeState[MAX_INPUT_MOUSE];
	byte ButtonMap[MAX_INPUT_MOUSE];

	Vector3 MouseCurStatus;
	Vector3 MouseBeforeStatus;
	Vector3 MouseMoveValue;

	DWORD DoubleClickTime;
	DWORD StartDoubleClick[MAX_INPUT_MOUSE];
	int ButtonCount[MAX_INPUT_MOUSE];

	int WheelDelta = 0.0f;
};

