#pragma once

class Perspective;
class Viewport;

class Context
{
private:
	Context();
	~Context();

public:
	static Context* Get();
	static void Create();
	static void Delete();

	void Update();
	void Render();

	Matrix GetViewMatrix() { return ViewMatrix; }
	Matrix Projection();

	Perspective* GetPerspective() { return PerspectiveView; }
	Viewport* GetViewport() { return View; }

private:
	static Context* Instance;

	Perspective* PerspectiveView;
	Viewport* View;

	Vector3 Position;
	Matrix ViewMatrix;
};

