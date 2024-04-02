#include "Libraries.h"
#include "Framework.h"
#include "GameManager.h"

#include "Scenes/TestScene.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
	SceneManager::Get()->Add("Test", new TestScene());

	CallScene("Test");
}

GameManager::~GameManager()
{
}

GameManager* GameManager::Get()
{
	if (Instance == nullptr)
		Create();

	return Instance;
}

void GameManager::Create()
{
	if (Instance == nullptr)
		Instance = new GameManager();

	{
		SceneManager::Get();
		Keyboard::Get();
		Timer::Get();
	}

	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(D3D::GetDesc().Handle);
		ImGui_ImplDX11_Init(D3D::GetDevice(), D3D::GetDC());
	}
}

void GameManager::Destroy()
{
	{
		Timer::Get();
		Keyboard::Get();

		SceneManager::Destroy();
	}

	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		ImGui::DestroyContext();
	}

	delete Instance;
}

void GameManager::Update()
{
	if (CurScene == nullptr)
		return;

	CurScene->Update();
}

void GameManager::Render()
{
	D3D::Get()->Clear();

	if (CurScene == nullptr)
		return;

	CurScene->PreRender();
	CurScene->Render();
	CurScene->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CurScene->GUIRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	D3D::Get()->Present();
}

void GameManager::CallScene(string Key)
{
	Scene* scene = SceneManager::Get()->Call(Key);
	if (scene == nullptr)
		return;

	if (CurScene != nullptr)
		CurScene->Disable();

	CurScene = scene;
	CurScene->Initialize();
}
