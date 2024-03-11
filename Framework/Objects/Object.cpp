#include "Libraries.h"
#include "Framework.h"
#include "Object.h"
#include "Framework/Managers/ShaderManager.h"

Object::Object(const Vector2 Pos, const Vector2 Size)
{
	VShader = ShaderManager::AddVS(L"VertexShader.hlsl");
	PShader = ShaderManager::AddPS(L"PixelShader.hlsl");

	float left = Pos.X - Size.X * 0.5f;
	float right = Pos.X + Size.X * 0.5f;
	float top = Pos.Y + Size.Y * 0.5f;
	float bottom = Pos.Y - Size.Y * 0.5f;

	Vertices.emplace_back(left, top, 0.0f);
	Vertices.emplace_back(right, top, 0.0f);
	Vertices.emplace_back(left, bottom, 0.0f);
	Vertices.emplace_back(right, bottom, 0.0f);

	Indices = { 0, 1, 2, 2, 1, 3 };

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(Vertex), Vertices.size());
	IBuffer = new IndexBuffer(Indices.data(), Indices.size());
}

Object::~Object()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
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

	D3D::GetDC()->DrawIndexed(Indices.size(), 0, 0);
}
