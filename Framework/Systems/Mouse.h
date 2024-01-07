#pragma once

#define MAX_INPUT_MOUSE 8

enum class MouseRotation : int
{
	NONE = 0,
	LEFT,
	RIGHT,
};

bool operator==(const int& value1, const MouseRotation& value2)
{
	return value1 == static_cast<int>(value2);	
}

bool operator!=(const int& value1, const MouseRotation & value2)
{
	return value1 != static_cast<int>(value2);
}

enum class ButtonInputState : int
{
	NONE = 0,
	DOWN,
	UP,
	PRESS,
	DBLCLK,
};

bool operator==(const int& value1, const ButtonInputState& value2)
{
	return value1 == static_cast<int>(value2);
}

bool operator!=(const int& value1, const ButtonInputState& value2)
{
	return value1 != static_cast<int>(value2);
}

class Mouse
{
private:
	Mouse();
	~Mouse();

public:
	void SetHandle(HWND handle)
	{
		this->Handle = handle;
	}

	static Mouse* Get();

	static void Create();
	static void Delete();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);
	Vector3 GetPosition() { return Position; }

	bool IsDown(DWORD button)
	{
		return ButtonMap[button] == ButtonInputState::DOWN;
	}
	bool IsUp(DWORD button)
	{
		return ButtonMap[button] == ButtonInputState::UP;
	}
	bool IsPress(DWORD button)
	{
		return ButtonMap[button] == ButtonInputState::PRESS;
	}

	Vector3 GetMoveValue()
	{
		return WheelMoveValue;
	}

private:
	static Mouse* Instance;

	HWND Handle;
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

