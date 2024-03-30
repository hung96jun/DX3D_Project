#pragma once

class GameManager
{
private:
	GameManager();
	~GameManager();

public:
	static GameManager* Get();
	static void Destroy();

	void Create();

	void Update();
	void Render();


private:
	static GameManager* Instance;

};

