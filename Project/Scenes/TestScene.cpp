#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"

#include "Renders/Material.h"

TestScene::TestScene()
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(L"SimpleColorShader");
	PShader = ShaderManager::Get()->AddPS(L"SimpleColorShader");

	{
		// Front
		Vertices.emplace_back(-0.5f, -0.5f, 0.0f);
		Vertices.emplace_back(-0.5f, +0.5f, 0.0f);
		Vertices.emplace_back(+0.5f, -0.5f, 0.0f);
		Vertices.emplace_back(+0.5f, +0.5f, 0.0f);
		
		Indices =
		{
			//0, 1, 3, 2, 0
			0, 1, 2, 2, 1, 3,
		};
	}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(Vertex), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));
	WBuffer = new MatrixBuffer();

	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

TestScene::~TestScene()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void TestScene::Initialize()
{
}

void TestScene::Destroy()
{
}

void TestScene::Update()
{
	Transform.SetPosition(Pos);
	Transform.SetRotation(Rot);
	Transform.SetScale(Scale);

	Transform.Update();
}

void TestScene::Render()
{
	VBuffer->Set();
	IBuffer->Set();

	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void TestScene::GUIRender()
{
	ImGui::Begin("Test");

	string log = "";
	log += "FPS : " + to_string(Time::Get()->GetFPS());
	ImGui::Text(log.c_str());

	float pos[3];
	pos[0] = Pos.X;
	pos[1] = Pos.Y;
	pos[2] = Pos.Z;
	ImGui::DragFloat3("\nPosition", pos, 0.01f, -1.0f, 1.0f);
	Pos.X = pos[0];
	Pos.Y = pos[1];
	Pos.Z = pos[2];

	float scale[3];
	scale[0] = Scale.X;
	scale[1] = Scale.Y;
	scale[2] = Scale.Z;
	ImGui::DragFloat3("\nScale", scale, 0.01f, -1.0f, 1.0f);
	Scale.X = scale[0];
	Scale.Y = scale[1];
	Scale.Z = scale[2];

	ImGui::End();
}
