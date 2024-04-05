#pragma once

class Perspective;
class Viewport;
class Camera;

class Context
{
private:
	Context();
	~Context();

public:
	static Context* Get();
	static void Destroy();

	void Update();
	void Render();

	Perspective* GetPerspective() { return Perspec; }
	Viewport* GetViewport() { return View; }
	Camera* GetCamera() { return Cam; }

	Matrix GetView();
	Matrix GetProjection();

private:
	static Context* Instance;

	Perspective* Perspec;
	Viewport* View;
	Camera* Cam;
};

