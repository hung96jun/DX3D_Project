#pragma once
#include "Framework/Managers/ProjectManager.h"

class EditorManager : public ProjectManager
{
private:
	EditorManager();
	~EditorManager();

public:
	static EditorManager* Get();
	static void Create();
	static void Destroy();

	virtual void Update() final;
	virtual void Render() final;

private:
	static EditorManager* Instance;
};

