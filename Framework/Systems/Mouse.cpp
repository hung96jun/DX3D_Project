#include "Libraries.h"
#include "Framework.h"
#include "Utilities/Debug.h"

Mouse* Mouse::Instance = nullptr;

Mouse::Mouse()
{
	CONSTRUCTOR_DEBUG();

	Position = Vector3::ZeroVector();
	MouseCurStatus = Vector3::ZeroVector();
	MouseBeforeStatus = Vector3::ZeroVector();
	MouseMoveValue = Vector3::ZeroVector();

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
	DESTRUCTOR_DEBUG();
}

Mouse* Mouse::Get()
{
	if (Instance == nullptr)
		Instance = new Mouse();

	return Instance;
}

void Mouse::Destroyt()
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

	MouseBeforeStatus.X = MouseCurStatus.X;
	MouseBeforeStatus.Y = MouseCurStatus.Y;

	MouseCurStatus.X = static_cast<float>(point.x);
	MouseCurStatus.Y = static_cast<float>(point.y);

	MouseMoveValue = MouseCurStatus - MouseBeforeStatus;
	MouseBeforeStatus.Z = MouseCurStatus.Z;

	DWORD buttonStatus = static_cast<DWORD>(GetTickCount64());
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (ButtonMap[i] == static_cast<byte>(ButtonInputState::DOWN))
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

		if (ButtonMap[i] == static_cast<byte>(ButtonInputState::UP))
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
			}
		}
	}

	WheelDelta = 0.0f;
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
		MouseBeforeStatus.Z = MouseCurStatus.Z;
		MouseCurStatus.Z += static_cast<float>(wheelValue);
	}

	return TRUE;
}
