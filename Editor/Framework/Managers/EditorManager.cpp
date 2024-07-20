#include "Framework.h"
#include "EditorManager.h"

#include "Scenes/ModelEditor.h"

EditorManager* EditorManager::Instance = nullptr;

EditorManager::EditorManager()
{
	CONSTRUCTOR_DEBUG();

	SceneManager::Get()->Add("ModelEditor", new ModelEditor());
	//SceneManager::Get()->Add("Test", new TestScene());
	////SceneManager::Get()->Add("Texture", new TextureScene());

	ActiveScene("ModelEditor");
	//ActiveScene("Test");
	////CallScene("Texture");
}

EditorManager::~EditorManager()
{
	DESTRUCTOR_DEBUG();
}

EditorManager* EditorManager::Get()
{
	if (Instance == nullptr)
		Create();

	return Instance;
}

void EditorManager::Create()
{
	if (Instance == nullptr)
		Instance = new EditorManager();

	SUPER::CreateManager();
}

void EditorManager::Destroy()
{
	SUPER::DestroyManager();

	delete Instance;
}

void EditorManager::Update()
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

void EditorManager::Render()
{
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
