#include "Framework.h"

Context* Context::Instance = nullptr;

Context::Context()
{
	WindowDesc desc = D3D::GetDesc();

	Perspec = new Perspective(static_cast<float>(desc.Width), static_cast<float>(desc.Height));
	View = new Viewport(static_cast<float>(desc.Width), static_cast<float>(desc.Height));
	
}

Context::~Context()
{
	SAFE_DELETE(Perspec);
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
	Perspec->GetMatrix(&projection);

	return projection;
}
