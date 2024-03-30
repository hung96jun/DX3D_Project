#include "Libraries.h"
#include "Framework.h"
#include "Object.h"
#include "Framework/Managers/ShaderManager.h"

Object::Object(const Vector2 Pos, const Vector2 Size)
{
	VShader = ShaderManager::Get()->AddVS(L"VertexShader.hlsl");
	PShader = ShaderManager::Get()->AddPS(L"PixelShader.hlsl");

	float left = Pos.X - Size.X;
	float right = Pos.X + Size.X;
	float top = Pos.Y + Size.Y;
	float bottom = Pos.Y - Size.Y;

	Vertices.emplace_back(left, top, 0.0f, 1.0f, 0.0f, 0.0f);
	Vertices.emplace_back(right, top, 0.0f, 1.0f, 0.0f, 0.0f);
	Vertices.emplace_back(left, bottom, 0.0f, 1.0f, 0.0f, 0.0f);
	Vertices.emplace_back(right, bottom, 0.0f, 1.0f, 0.0f, 0.0f);

	Indices = { 0, 1, 2, 2, 1, 3 };

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), sizeof(Indices.size()));
}

Object::~Object()
{
	SAFE_DELETE(VBuffer);
}

void Object::Update()
{
}

void Object::Render()
{
	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}
