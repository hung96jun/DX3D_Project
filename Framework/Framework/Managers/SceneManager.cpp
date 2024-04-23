#include "Libraries.h"
#include "Framework.h"
#include "SceneManager.h"

#include "Framework/Scene.h"

SceneManager* SceneManager::Instance = nullptr;
map<string, Scene*> SceneManager::Scenes;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> scenes : Scenes)
	{
		if (scenes.second != nullptr)
			delete scenes.second;
	}
}

SceneManager* SceneManager::Get()
{
	if (Instance == nullptr)
		Instance = new SceneManager();

	return Instance;
}

void SceneManager::Destroy()
{
	delete Instance;
}

void SceneManager::Add(const string Key, Scene* AddScene)
{
	if (Scenes.count(Key) != 0)
		return;

	pair<string, Scene*> scene;
	scene.first = Key;
	scene.second = AddScene;

	Scenes.insert(scene);
}

void SceneManager::Remove(const string Key)
{
	if (Scenes.count(Key) == 1)
		Scenes.erase(Key);
}

Scene* SceneManager::Call(string Key)
{
	if (Scenes.count(Key) == 0)
		return nullptr;

	//Scene* scene = Scenes[Key];
	//if (scene == CurScene)
	//	return nullptr;

	//CurScene->Disable();
	//CurScene = scene;
	//CurScene->Initialize();

	return Scenes[Key];
}
