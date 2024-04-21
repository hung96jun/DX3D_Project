#pragma once

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
	void CallScene(string Key);

private:
	static EditorSceneManager* Instance;
	
};

