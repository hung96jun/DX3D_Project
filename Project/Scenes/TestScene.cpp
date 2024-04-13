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

	Vertices.emplace_back(+0.0f, +0.5f, 0.0f, 0.5f, 0.5f, 1.0f);
	Vertices.emplace_back(+0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f);
	Vertices.emplace_back(-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f);

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), Vertices.size());
	WBuffer = new MatrixBuffer();
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

	Matrix mat = s * r * t;

	WBuffer->Set(mat);
}

void TestScene::Render()
{
	//TestObject->Render();

	//WBuffer->SetVS(0);
	VBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->Draw(Vertices.size(), 0);
}

void TestScene::GUIRender()
{
	//ImGui::Begin("Test");
	//
	//TestObject->GUIRender();
	//
	//ImGui::End();
}
