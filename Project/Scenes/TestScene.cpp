#include "stdafx.h"
#include "TestScene.h"

void TestScene::Initializer()
{
	//VShader = ShaderManager::AddVS(L"Vertex.hlsl");
	////PShader = ShaderManager::AddPS(L"Pixel.hlsl");

	//Vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	//Vertices[1].Position = Vector3(+0.0f, +0.5f, 0.0f);
	//Vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);

	//D3D11_BUFFER_DESC desc;
	//ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	//desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.ByteWidth = sizeof(Vertex) * 3;
	//desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//D3D11_SUBRESOURCE_DATA subResource;
	//ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	//subResource.pSysMem = Vertices;

	//CHECK(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &VertexBuffer));

	Test = new Object(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f));
}

void TestScene::Destroy()
{
	//SAFE_DELETE(VShader);
	//SAFE_RELEASE(VertexBuffer);

	SAFE_DELETE(Test);
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	//UINT stride = sizeof(Vertex);
	//UINT offset = 3;

	//D3D::GetDC()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//D3D::GetDC()->Draw(3, 0);

	Test->Render();
}
