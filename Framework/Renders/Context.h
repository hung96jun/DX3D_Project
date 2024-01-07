#pragma once

class Context
{
private:
	Context();
	~Context();

	void Update();
	void Render();

	Matrix GetView() { return View; }
	Matrix GetProjection();

public:
	static Context* Get();

	static void Create();
	static void Delete();


private:
	static Context* Instance;

	Vector3 Position;
	Matrix View;
};

