#include "Libraries.h"
#include "Framework.h"
#include "Context.h"

Context* Context::Instance = nullptr;

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	PerspectiveView = new Perspective(desc.Width, desc.Height);
	View = new Viewport(desc.Width, desc.Height);

	Position = Vector3(29.5f, 16.5f, -50.0f);
	
	Vector3 forward = Vector3::Forward();
	Vector3 up = Vector3::Up();
	Vector3 focusPosition = Position + forward;

	XMMatrixLookAtLH(Position.GetValue(), focusPosition.GetValue(), up.GetValue());
}

Context::~Context()
{
	SAFE_DELETE(PerspectiveView);
	SAFE_DELETE(View);
}

Context* Context::Get()
{
	assert(Instance != nullptr);
	return Instance;
}

void Context::Create()
{
	assert(Instance == nullptr);
	Instance = new Context();
}

void Context::Delete()
{
	SAFE_DELETE(Instance);
}

void Context::Update()
{
}

void Context::Render()
{
	View->RSSetViewport();
}

Matrix Context::Projection()
{
	Matrix projection;
	PerspectiveView->GetMatrix(&projection);

	return projection;
}
