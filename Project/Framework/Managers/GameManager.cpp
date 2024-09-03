#include "Framework.h"
#include "GameManager.h"

#include "Scenes/TestScene.h"
#include "Scenes/TextureScene.h"
#include "Scenes/TerrainTestScene.h"
#include "Scenes/InstanceScene2.h"
#include "Scenes/ModelScene.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
	:ProjectManager()
{
	CONSTRUCTOR_DEBUG();

	//SceneManager::Get()->Add("Test", new TestScene());
	//SceneManager::Get()->Add("Terrain", new TerrainTestScene());
	
	//SceneManager::Get()->Add("Texture", new TextureScene());

	//SceneManager::Get()->Add("Instance", new InstanceScene2());
	SceneManager::Get()->Add("Model", new ModelScene());

	//ActiveScene("Test");
	//ActiveScene("Terrain");
	
	//ActiveScene("Texture");

	//ActiveScene("Instance");

	ActiveScene("Model");
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

	SUPER::CreateManager();
}

void GameManager::Destroy()
{
	SUPER::DestroyManager();

	delete Instance;
}

void GameManager::Update()
{
	if (ActiveSceneCount == 0)
		return;

	Time::Get()->Update();
	Timer::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();

	Context::Get()->Update();
	for (pair<string, Scene*> scene : Scenes)
	{
		if (scene.second->IsActive() == false)
			continue;

		scene.second->Update();
	}
}

void GameManager::Render()
{
	//D3D::Get()->SetRenderTarget();
	D3D::Get()->Clear(D3D::GetDesc().Background);

	if (ActiveSceneCount == 0)
		return;

	Context::Get()->Render();

	for (pair<string, Scene*> scene : Scenes)
	{
		if (scene.second->IsActive() == false)
			continue;

		scene.second->PreRender();
		scene.second->Render();
		scene.second->PostRender();
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Context::Get()->GUIRender();
	for (pair<string, Scene*> scene : Scenes)
	{
		if (scene.second->IsActive() == false)
			continue;

		scene.second->GUIRender();
	}
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	D3D::Get()->Present();
}

//void GameManager::ActiveScene(string Key)
//{
//	Scene* scene = nullptr;
//	if (Scenes.count(Key) > 0)
//		scene = Scenes[Key];
//	else
//	{
//		scene = SceneManager::Get()->Call(Key);
//		pair<string, Scene*> scenePair;
//		scenePair.first = Key;
//		scenePair.second = scene;
//
//		Scenes.insert(scenePair);
//	}
//
//	if (scene == nullptr) return;
//
//	scene->Initialize();
//	scene->OnActive();
//	++ActiveSceneCount;
//}
//
//void GameManager::DisableScene(string Key)
//{
//	if (Scenes.count(Key) == 0)
//		return;
//
//	Scenes[Key]->Disable();
//	Scenes[Key]->OnDisable();
//	--ActiveSceneCount;
//}
