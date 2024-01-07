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

	return WPARAM();
}

void Window::Create()
{
}

void Window::Destroy()
{
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

void Window::MainRender()
{
}
