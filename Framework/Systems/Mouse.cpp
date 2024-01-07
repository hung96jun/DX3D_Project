#include "Framework.h"
#include "Mouse.h"

Mouse::Mouse()
{
	Position = Vector3::ZeroVector();
	WheelCurStatus = Vector3::ZeroVector();
	WheelBeforeStatus = Vector3::ZeroVector();
	WheelMoveValue = Vector3::ZeroVector();

	ZeroMemory(ButtonCurState, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(ButtonBeforeState, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(ButtonMap, sizeof(byte) * MAX_INPUT_MOUSE);

	ZeroMemory(StartDoubleClick, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(ButtonCount, sizeof(int) * MAX_INPUT_MOUSE);
	
	DoubleClickTime = GetDoubleClickTime();
	StartDoubleClick[0] = static_cast<DWORD>(GetTickCount64());
	
	for (int i = 1; i < MAX_INPUT_MOUSE; i++)
		StartDoubleClick[i] = StartDoubleClick[0];

	DWORD tLine = 0;
	SystemParametersInfoA(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);
}

Mouse::~Mouse()
{
}

Mouse* Mouse::Get()
{
	assert(Instance != nullptr);
	return Instance;
}

void Mouse::Create()
{
	assert(Instance == nullptr);
	Instance = new Mouse();
}

void Mouse::Delete()
{
	SAFE_DELETE(Instance);
}

void Mouse::Update()
{
	memcpy(ButtonBeforeState, ButtonCurState, sizeof(ButtonBeforeState));

	ZeroMemory(ButtonCurState, sizeof(ButtonCurState));
	ZeroMemory(ButtonMap, sizeof(ButtonMap));

	ButtonCurState[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	ButtonCurState[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	ButtonCurState[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		int beforeState = ButtonBeforeState[i];
		int curState = ButtonCurState[i];

		if (beforeState == 0 && curState == 1)
			ButtonMap[i] = static_cast<byte>(ButtonInputState::DOWN);
		else if (beforeState == 1 && curState == 0)
			ButtonMap[i] = static_cast<byte>(ButtonInputState::UP);
		else if (beforeState == 1 && curState == 1)
			ButtonMap[i] = static_cast<byte>(ButtonInputState::PRESS);
		else
			ButtonMap[i] = static_cast<byte>(ButtonInputState::NONE);
	}

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(Handle, &point);

	WheelBeforeStatus.X = WheelCurStatus.X;
	WheelBeforeStatus.Y = WheelCurStatus.Y;

	WheelCurStatus.X = static_cast<float>(point.x);
	WheelCurStatus.Y = static_cast<float>(point.y);

	WheelMoveValue = WheelCurStatus - WheelBeforeStatus;
	WheelBeforeStatus.Z = WheelCurStatus.Z;

	DWORD buttonStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (ButtonMap[i] == ButtonInputState::DOWN)
		{
			if (ButtonCount[i] == 1)
			{
				if (buttonStatus - StartDoubleClick[i] >= DoubleClickTime)
					ButtonCount[i] = 0;
			}
			ButtonCount[i]++;

			if (ButtonCount[i] == 1)
				StartDoubleClick[i] = buttonStatus;
		}

		if (ButtonMap[i] == ButtonInputState::UP)
		{
			if (ButtonCount[i] == 1)
			{
				if (buttonStatus - StartDoubleClick[i] >= DoubleClickTime)
					ButtonCount[i] = 0;
			}
			else if (ButtonCount[i] == 2)
			{
				if (buttonStatus - StartDoubleClick[i] <= DoubleClickTime)
					ButtonMap[i] = static_cast<byte>(ButtonInputState::DBLCLK);

				ButtonCount[i] = 0;
			} // if
		} // for(i)
	}
}

LRESULT Mouse::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		Position.X = static_cast<float>(LOWORD(lParam));
		Position.Y = static_cast<float>(HIWORD(lParam));
	}

	if (message == WM_MOUSEWHEEL)
	{
		short wheelValue = static_cast<short>(HIWORD(wParam));
		WheelBeforeStatus.Z = WheelCurStatus.Z;
		WheelCurStatus.Z += static_cast<float>(wheelValue);
	}

	return TRUE;
}
