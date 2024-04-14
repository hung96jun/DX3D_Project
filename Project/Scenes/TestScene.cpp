#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"
#include "Objects/Environment/Grid.h"

TestScene::TestScene()
{
	//TestObject = new Object({ 0.0f, 0.0f }, { 0.3f, 0.3f });
	//TestObject = new Object();

	VShader = ShaderManager::Get()->AddVS(L"SimpleShader");
	PShader = ShaderManager::Get()->AddPS(L"SimpleShader");

	//Vertices.emplace_back(+0.0f, +0.5f, 0.0f, 1.0f, 0.5f, 0.5f);
	//Vertices.emplace_back(+0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.5f);
	//Vertices.emplace_back(-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f);

	Vertices.emplace_back(-0.5f, -0.5f, 0.0f, Color[0], Color[1], Color[2]);
	Vertices.emplace_back(-0.5f, +0.5f, 0.0f, Color[0], Color[1], Color[2]);
	Vertices.emplace_back(+0.5f, -0.5f, 0.0f, Color[0], Color[1], Color[2]);
	//Vertices.emplace_back(+0.5f, +0.5f, 0.0f, 1.0f, 0.5f, 0.5f);

	Indices = { 0, 1, 2, 2, 1, 3 };

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), Vertices.size());
	IBuffer = new IndexBuffer(Indices.data(), Indices.size());
	WBuffer = new MatrixBuffer();

	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

TestScene::~TestScene()
{
	//SAFE_DELETE(TestObject);

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void TestScene::Initialize()
{
}

void TestScene::Destory()
{
}

void TestScene::Update()
{
	//TestObject->Update();


	Matrix s, r, t;
	s = XMMatrixScaling(Scale.X, Scale.Y, Scale.Z);
	r = XMMatrixRotationZ(0.0f);
	t = XMMatrixTranslation(Pos.X, Pos.Y, Pos.Z);

	World = s * r * t;
}

void TestScene::Render()
{
	//TestObject->Render();

	WBuffer->Set(World);
	WBuffer->SetVS(0);
	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->Draw(Vertices.size(), 0);
	//D3D::GetDC()->DrawIndexed(2, 0, 0);
}

void TestScene::GUIRender()
{
	//ImGui::Begin("Test");
	//
	//TestObject->GUIRender();
	//
	//ImGui::End();

	ImGui::Begin("Test");

	float pos[3];
	pos[0] = Pos.X;
	pos[1] = Pos.Y;
	pos[2] = Pos.Z;
	ImGui::DragFloat3("Position", pos, 0.01f, -1.0f, 1.0f);
	Pos.X = pos[0];
	Pos.Y = pos[1];
	Pos.Z = pos[2];

	string debug = "";
	debug += "\nPos : " + Pos.ToString();
	ImGui::Text(debug.c_str());

	//ImGui::ColorEdit3("Color", Color);
	//Vertices[0].Color = {Color[0], Color[1], Color[2], 1.0f};
	//Vertices[1].Color = {Color[0], Color[1], Color[2], 1.0f};
	//Vertices[2].Color = {Color[0], Color[1], Color[2], 1.0f};
	//VBuffer->Update(Vertices.data(), Vertices.size());

	ImGui::End();
}
