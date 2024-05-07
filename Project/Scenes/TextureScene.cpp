#include "stdafx.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(L"TextureShader");
	PShader = ShaderManager::Get()->AddPS(L"TextureShader");

	Vertices.emplace_back(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.5f);
	Vertices.emplace_back(-0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.5f);
	Vertices.emplace_back(+0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.5f);
	Vertices.emplace_back(+0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.5f);

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexColor) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA resource;
		ZeroMemory(&resource, sizeof(D3D11_SUBRESOURCE_DATA));
		resource.pSysMem = Vertices.data();

		D3D::GetDevice()->CreateBuffer(&desc, &resource, &VBuffer);
	}

	Indices = { 0, 1, 2, 2, 1, 3 };
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA resource;
		ZeroMemory(&resource, sizeof(D3D11_SUBRESOURCE_DATA));
		resource.pSysMem = Indices.data();
		D3D::GetDevice()->CreateBuffer(&desc, &resource, &IBuffer);
	}

	WBuffer = new MatrixBuffer();
	Tex = Texture::Add(L"Landscape/Box.png");

	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

TextureScene::~TextureScene()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(VBuffer);
	SAFE_RELEASE(IBuffer);

	SAFE_DELETE(WBuffer);
	Tex->Destroy();
}

void TextureScene::Initialize()
{
}

void TextureScene::Destory()
{
}

void TextureScene::Update()
{
	Matrix s, r, t;
	s = XMMatrixScaling(Scale.X, Scale.Y, Scale.Z);
	r = XMMatrixRotationZ(0.0f);
	t = XMMatrixTranslation(Pos.X, Pos.Y, Pos.Z);

	World = s * r * t;
}

void TextureScene::Render()
{
	WBuffer->Set(World);
	WBuffer->SetVS(0);
	//VBuffer->Set();
	//IBuffer->Set();

	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &VBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(IBuffer, DXGI_FORMAT_R32_UINT, 0);
	Tex->PSSet(0);

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void TextureScene::GUIRender()
{
}
