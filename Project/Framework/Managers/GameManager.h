#pragma once
#include "Framework/Managers/ProjectManager.h"

class GameManager : public ProjectManager
{
private:
	GameManager();
	~GameManager();

public:
	static GameManager* Get();
	static void Create();
	static void Destroy();

	virtual void Update() final;
	virtual void Render() final;

//private:
//	//void CallScene(string Key);
//	void ActiveScene(string Key);
//	void DisableScene(string Key);

private:
	static GameManager* Instance;

	//Scene* CurScene = nullptr;
	//map<string, Scene*> Scenes;
	//int ActiveSceneCount = 0;
};

