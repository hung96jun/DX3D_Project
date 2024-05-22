#pragma once

class Scene;

class GameManager
{
private:
	GameManager();
	~GameManager();

public:
	static GameManager* Get();
	static void Create();
	static void Destroy();

	void Update();
	void Render();

private:
	//void CallScene(string Key);
	void ActiveScene(string Key);
	void DisableScene(string Key);

private:
	static GameManager* Instance;

	//Scene* CurScene = nullptr;
	map<string, Scene*> Scenes;
	int ActiveSceneCount = 0;
};

