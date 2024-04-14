#include "Framework.h"

Context* Context::Instance = nullptr;

Context::Context()
{
	WindowDesc desc = D3D::GetDesc();

	Persp = new Perspective(static_cast<float>(desc.Width), static_cast<float>(desc.Height), 0.1f, 1000.0f);
	Ortho = new Orthographic(static_cast<float>(desc.Width), static_cast<float>(desc.Height), -1.0f, 1.0f);
	View = new Viewport(static_cast<float>(desc.Width), static_cast<float>(desc.Height));
	Cam = new FreeCamera();
}

Context::~Context()
{
	SAFE_DELETE(Persp);
	SAFE_DELETE(Ortho);
	SAFE_DELETE(View);
	SAFE_DELETE(Cam);
}

Context* Context::Get()
{
	if (Instance == nullptr)
		Instance = new Context();

	return Instance;
}

void Context::Destroy()
{
	delete Instance;
}

void Context::Update()
{
	Cam->Update();
}

void Context::Render()
{
	View->RSSetViewport();
	Cam->Set();
	Persp->Set();
	//Ortho->Set();
}

void Context::GUIRender()
{
	Cam->GUIRender();
}

Matrix Context::GetView()
{
	Matrix view;
	Cam->GetMatrix(&view);

	return view;
}

Matrix Context::GetProjection()
{
	Matrix projection;
	//Persp->GetMatrix(&projection);
	Ortho->GetMatrix(&projection);

	return projection;
}
