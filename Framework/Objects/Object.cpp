#include "Object.h"

Object::Object(const wstring ShaderFile)
{
	wstring file = ShaderFile + L".hlsl";
	VShader = ShaderManager::Get()->AddVS(file);
	PShader = ShaderManager::Get()->AddPS(file);

	//VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), static_cast<UINT>(Vertices.size()));
	//IBuffer = new IndexBuffer(Indices.data(), sizeof(Indices.size()));

	
}

Object::~Object()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	//SAFE_DELETE(WBuffer);
}

void Object::Update()
{
	Transform.Update();
}

void Object::Render()
{
	//if (VBuffer == nullptr || IBuffer == nullptr ||
	//	VShader == nullptr || PShader == nullptr)
	//	return;

	//VBuffer->Set();
	//IBuffer->Set();

	//WBuffer->Set(Transform.GetWorld());
	//WBuffer->SetVS(0);

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}
