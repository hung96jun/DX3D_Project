#include "Libraries.h"
#include "Framework.h"
#include "GameManager.h"

#include "Scenes/GridScene.h"
#include "Scenes/TestScene.h"
#include "Scenes/TextureScene.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
	CONSTRUCTOR_DEBUG();

	SceneManager::Get()->Add("Grid", new GridScene());

	SceneManager::Get()->Add("Test", new TestScene());
	//SceneManager::Get()->Add("Texture", new TextureScene());

	//CallScene("Grid");
	CallScene("Test");
	//CallScene("Texture");
}

GameManager::~GameManager()
{
	DESTRUCTOR_DEBUG();
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
		ShaderManager::Get();
		Context::Get();

		Keyboard::Get();
		Mouse::Get();
		Timer::Get();
		Time::Get();
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
		Texture::Destroy();
		Time::Destroy();
		Timer::Destroy();
		Mouse::Destroyt();
		Keyboard::Destroy();

		D3D::Destroy();
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

void GameManager::Update()
{
	if (CurScene == nullptr)
		return;

	Time::Get()->Update();
	Timer::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();

	Context::Get()->Update();
	CurScene->Update();
}

void GameManager::Render()
{
	D3D::Get()->Clear();

	if (CurScene == nullptr)
		return;

	Context::Get()->Render();

	//CurScene->PreRender();
	CurScene->Render();
	//CurScene->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Context::Get()->GUIRender();
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
