#include "Framework.h"
#include "Renders/States/RasterizerState.h"
#include "Renders/States/SamplerState.h"

Context* Context::Instance = nullptr;

Context::Context()
{
	CONSTRUCTOR_DEBUG();

	WindowDesc desc = D3D::GetDesc();

	Persp = new Perspective(static_cast<float>(desc.Width), static_cast<float>(desc.Height), 0.1f, 1000.0f);
	Ortho = new Orthographic(static_cast<float>(desc.Width), static_cast<float>(desc.Height), -1.0f, 1.0f);
	View = new Viewport(static_cast<float>(desc.Width), static_cast<float>(desc.Height), 0.0f, 0.0f, 0.0f, 1.0f);
	Cam = new FreeCamera();

	Rasterizer[0] = new RasterizerState();
	Rasterizer[1] = new RasterizerState();
	Rasterizer[1]->FillMode(D3D11_FILL_WIREFRAME);
	
	Sampler = new SamplerState();
	Sampler->SetState();

	VPBuffer = new ViewProjectionBuffer();
}

Context::~Context()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Persp);
	SAFE_DELETE(Ortho);
	SAFE_DELETE(View);
	SAFE_DELETE(Cam);

	SAFE_DELETE(Rasterizer[0]);
	SAFE_DELETE(Rasterizer[1]);
	SAFE_DELETE(Sampler);

	SAFE_DELETE(VPBuffer);
}

Context* Context::Get()
{
	if (Instance == nullptr)
		Instance = new Context();

	return Instance;
}

void Context::Destroy()
{
	SAFE_DELETE(Instance);
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

	VPBuffer->Set(Cam->GetViewMatrix(), Cam->GetTransform().GetWorld(), Persp->GetMatrix());
	VPBuffer->SetVS(1);

	if (bWireMode == false)
		Rasterizer[0]->SetState();
	else
		Rasterizer[1]->SetState();
}

void Context::GUIRender()
{
	Cam->GUIRender();

	ImGui::Begin("Context");

	if (ImGui::Button("Fill Mode"))
	{
		bWireMode = bWireMode == true ? false : true;
	}

	ImGui::End();
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
	Persp->GetMatrix(&projection);
	//Ortho->GetMatrix(&projection);

	return projection;
}
