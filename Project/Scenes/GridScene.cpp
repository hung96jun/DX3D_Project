#include "stdafx.h"
#include "GridScene.h"

GridScene::GridScene()
{
	Vertices.resize((Width + 1) * (Height + 1));

	for (UINT y = 0; y <= Height; y++)
	{
		for (UINT x = 0; x <= Width; x++)
		{
			UINT index = (Width + 1) * y + x;
			Vertices[index].Position.x = static_cast<float>(x);
			Vertices[index].Position.y = 0.0f;
			Vertices[index].Position.z = static_cast<float>(y);
		}
	}

	Indices.resize((Width * Height * 6));

	UINT index = 0;
	for (UINT y = 0; y < Height; y++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			Indices[index + 0] = (Width + 1) * y + x;
			Indices[index + 1] = (Width + 1) * (y + 1) + x;
			Indices[index + 2] = (Width + 1) * y + x + 1;
			Indices[index + 3] = (Width + 1) * y + x + 1;
			Indices[index + 4] = (Width + 1) * (y + 1) + x;
			Indices[index + 5] = (Width + 1) * (y + 1) + x + 1;

			index += 6;
		}
	}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(Vertex), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), Indices.size());
	WBuffer = new MatrixBuffer();
	Transform.SetTag("Grid");
	Transform.Update();

	VShader = ShaderManager::Get()->AddVS(L"GridShader");
	PShader = ShaderManager::Get()->AddPS(L"GridShader");
}

GridScene::~GridScene()
{
}

void GridScene::Disable()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void GridScene::Render()
{
	VBuffer->Set();
	IBuffer->Set();
	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(Indices.size(), VertexStart, 0);
}

void GridScene::GUIRender()
{
	string log;
	log = "FPS : " + to_string(Time::Get()->GetFPS());
	ImGui::Text(log.c_str());

	Transform.GUIRender();

	ImGui::DragInt("VertexStart", &VertexStart, 1, 0, Vertices.size());
}
