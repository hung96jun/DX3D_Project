#pragma once

class Perspective;
class Viewport;
class Camera;
class SamplerState;
class RasterizerState;

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

	Perspective* Persp = nullptr;
	Orthographic* Ortho = nullptr;
	Viewport* View = nullptr;
	Camera* Cam = nullptr;

	SamplerState* Sampler = nullptr;
	RasterizerState* Rasterizer[2] = { nullptr };

	bool bWireMode = false;
};

