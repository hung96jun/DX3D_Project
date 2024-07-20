#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
	CONSTRUCTOR_DEBUG();
}

ProjectManager::~ProjectManager()
{
	DESTRUCTOR_DEBUG();
}

void ProjectManager::CreateManager()
{
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

void ProjectManager::DestroyManager()
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
}

void ProjectManager::ActiveScene(string Key)
{
	Scene* scene = nullptr;
	if (Scenes.count(Key) > 0)
		scene = Scenes[Key];
	else
	{
		scene = SceneManager::Get()->Call(Key);
		pair<string, Scene*> scenePair;
		scenePair.first = Key;
		scenePair.second = scene;

		Scenes.insert(scenePair);
	}

	if (scene == nullptr) return;

	scene->Initialize();
	scene->OnActive();
	++ActiveSceneCount;
}

void ProjectManager::DisableScene(string Key)
{
	if (Scenes.count(Key) == 0)
		return;

	Scenes[Key]->Disable();
	Scenes[Key]->OnDisable();
	--ActiveSceneCount;
}
