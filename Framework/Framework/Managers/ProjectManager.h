#pragma once
#include "Libraries.h"
#include "Framework.h"
#include "Framework/Managers/SceneManager.h"

class Scene;

/**
* 파생 클래스에서는 싱글턴 클래스로 선언
* 파생 클래스의 Create 함수에서는 CreateManager 함수를 호출
* 파생 클래스의 Destroy 함수에서는 DestoryManager 함수를 호출
*/
class ProjectManager
{
protected:
	ProjectManager();
	~ProjectManager();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	static void CreateManager();
	static void DestroyManager();

	void ActiveScene(string Key);
	void DisableScene(string Key);

protected:
	map<string, Scene*> Scenes;
	int ActiveSceneCount = 0;
};

