#include "Libraries.h"
#include "Framework.h"
#include "EditorSceneManager.h"

///////////////////////////////////////////////////////////////////////////////
// Include the scene headers
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

EditorSceneManager* EditorSceneManager::Instance = nullptr;

EditorSceneManager::EditorSceneManager()
{
}

EditorSceneManager::~EditorSceneManager()
{
}

EditorSceneManager* EditorSceneManager::Get()
{
	if (Instance == nullptr)
		Create();

	return Instance;
}

void EditorSceneManager::Create()
{
	Instance = new EditorSceneManager();

	{
		SceneManager::Get();
		ShaderManager::Get();
		Context::Get();

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

void EditorSceneManager::Destroy()
{
	{
		Timer::Get();
		Keyboard::Get();

		Context::Destroy();
		ShaderManager::Destroy();
		SceneManager::Destroy();
	}

	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		ImGui::DestroyContext();
	}

	delete Instance;
}

void EditorSceneManager::Update()
{
	//if (CurScene == nullptr)
	//	return;

	Time::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();

	Context::Get()->Update();
	//CurScene->Update();
}

void EditorSceneManager::Render()
{
	D3D::Get()->Clear();

	//if (CurScene == nullptr)
	//	return;

	Context::Get()->Render();

	//CurScene->PreRender();
	//CurScene->Render();
	//CurScene->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Context::Get()->GUIRender();
	//CurScene->GUIRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	D3D::Get()->Present();
}

void EditorSceneManager::CallScene(string Key)
{
}
