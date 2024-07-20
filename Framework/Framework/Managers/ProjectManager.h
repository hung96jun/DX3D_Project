#pragma once
#include "Libraries.h"
#include "Framework.h"
#include "Framework/Managers/SceneManager.h"

class Scene;

/**
* �Ļ� Ŭ���������� �̱��� Ŭ������ ����
* �Ļ� Ŭ������ Create �Լ������� CreateManager �Լ��� ȣ��
* �Ļ� Ŭ������ Destroy �Լ������� DestoryManager �Լ��� ȣ��
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

