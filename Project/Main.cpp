#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"

#include "Scenes/TestScene.h"

void Main::Initializer()
{
	Push(new TestScene());
}

void Main::Ready()
{
}

void Main::Destroy()
{
	for (Scene* scene : Scenes)
	{
		scene->Destroy();
		SAFE_DELETE(scene);
	}
}

void Main::Update()
{
	for (Scene* scene : Scenes)
		scene->Update();
}

void Main::PreRender()
{
	for (Scene* scene : Scenes)
		scene->PreRender();
}

void Main::Render()
{
	for (Scene* scene : Scenes)
		scene->Render();
}

void Main::PostRender()
{
	for (Scene* scene : Scenes)
		scene->PostRender();
}

void Main::ResizeScreen()
{
	for (Scene* scene : Scenes)
		scene->ResizeScreen();
}

void Main::Push(Scene* scene)
{
	Scenes.push_back(scene);
	scene->Initializer();
}

// 프로그램 시작
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	D3DDesc desc;
	desc.AppName = L"DX3D_Project"; 
	desc.Instance = hInstance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = nullptr;
	desc.Width = 1280;
	desc.Height = 720;
	desc.Background = Color(0.3f, 0.3f, 0.3f, 1.0f);
	D3D::SetDesc(desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);

	SAFE_DELETE(main);

	return static_cast<int>(wParam);
}