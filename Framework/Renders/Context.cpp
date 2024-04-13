#include "Framework.h"

Context* Context::Instance = nullptr;

Context::Context()
{
	WindowDesc desc = D3D::GetDesc();

	Persp = new Perspective(static_cast<float>(desc.Width), static_cast<float>(desc.Height));
	Ortho = new Orthographic(static_cast<float>(desc.Width), static_cast<float>(desc.Height));
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
	//Persp->Set();
	Ortho->Set();
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
