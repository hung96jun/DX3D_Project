#include "Libraries.h"
#include "Framework.h"
#include "Window.h"
//#include "D3D.h"
#include "Scene.h"

Scene* Window::MainScene = nullptr;

WPARAM Window::Run(Scene* main)
{
	MainScene = main;
	Create();

	D3DDesc desc = D3D::GetDesc();

	D3D::Create();
	Keyboard::Create();
	Mouse::Create();

	Time::Create();
	Time::Get()->Start();

	Context::Create();
		
	MainScene->Initializer();

	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainRender();
		}
	}
	MainScene->Destroy();

	Context::Delete();
	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();
	D3D::Delete();

	Destroy();

	return WPARAM();
}

void Window::Create()
{
	D3DDesc desc = D3D::GetDesc();

	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.Instance;
	wndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	if (desc.bFullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = static_cast<DWORD>(desc.Width);
		devMode.dmPelsHeight = static_cast<DWORD>(desc.Height);
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW
		, desc.AppName.c_str()
		, desc.AppName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, nullptr
		, static_cast<HMENU>(nullptr)
		, desc.Instance
		, nullptr
	);
	assert(desc.Handle != NULL);
	D3D::SetDesc(desc);
}

void Window::Destroy()
{
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);

	
	switch (message)
	{
	case WM_SIZE:
	{
		if (MainScene != nullptr)
		{
			float width = static_cast<float>(LOWORD(lParam));
			float height = static_cast<float>(HIWORD(lParam));

			if (D3D::Get() != nullptr)
				D3D::Get()->ResizeScreen(width, height);

			MainScene->ResizeScreen();
		}
	}
		break;
	case WM_CLOSE:
	//[[fallthrough]]
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::MainRender()
{
	
}
