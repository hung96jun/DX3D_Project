#pragma once

class Scene;

class EditorSceneManager
{
private:
	EditorSceneManager();
	~EditorSceneManager();

public:
	static EditorSceneManager* Get();
	static void Create();
	static void Destroy();

	void Update();
	void Render();

private:
	//void CallScene(string Key);
	void ActiveScene(string Key);
	void DisableScene(string Key);

private:
	static EditorSceneManager* Instance;

	//Scene* CurScene = nullptr;
	map<string, Scene*> Scenes;
	int ActiveSceneCount = 0;
};

