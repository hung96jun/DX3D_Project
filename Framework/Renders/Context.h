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
	void GUIRender();

	Perspective* GetPerspective() { return Persp; }
	Viewport* GetViewport() { return View; }
	Camera* GetCamera() { return Cam; }

	Matrix GetView();
	Matrix GetProjection();

private:
	static Context* Instance;

	Perspective* Persp;
	Orthographic* Ortho;
	Viewport* View;
	Camera* Cam;
};

