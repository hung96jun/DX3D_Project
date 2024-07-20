#pragma once

using namespace std;
class Scene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* Get();
	static void Destroy();

	void Add(const string Key, Scene* AddScene);
	void Remove(const string Key);
	Scene* Call(string Key);

	//void Create();

private:
	static SceneManager* Instance;

	static map<string, Scene*> Scenes;
	//map<string, Scene*> ActiveScenes;
	//Scene* CurScene = nullptr;
};

