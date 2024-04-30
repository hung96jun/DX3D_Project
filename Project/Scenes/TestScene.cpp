#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"
#include "Objects/Environment/Grid.h"

TestScene::TestScene()
{
	//TestObject = new Object({ 0.0f, 0.0f }, { 0.3f, 0.3f });
	//TestObject = new Object();

	VShader = ShaderManager::Get()->AddVS(L"TextureShader");
	PShader = ShaderManager::Get()->AddPS(L"TextureShader");

	//{
	//	Vertices.emplace_back(-0.5f, -0.5f, +0.0f, 1.0f, 1.0f, 0.5f);
	//	Vertices.emplace_back(-0.5f, +0.5f, +0.0f, 1.0f, 1.0f, 0.5f);
	//	Vertices.emplace_back(+0.5f, -0.5f, +0.0f, 1.0f, 1.0f, 0.5f);
	//	Vertices.emplace_back(+0.5f, +0.5f, +0.0f, 1.0f, 1.0f, 0.5f);
	//
	//	Indices = { 0, 1, 2, 2, 1, 3 };
	//}

	{
		Vertices.emplace_back(-0.5f, -0.5f, +0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, +0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(+0.5f, -0.5f, +0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, +0.5f, 1.0f, 0.0f);
	
		Indices = { 0, 1, 2, 2, 1, 3 };
	}

	//{
	//	Vertices.emplace_back(-0.5f, -0.5f, +0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(-0.5f, +0.5f, +0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(+0.5f, -0.5f, +0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(+0.5f, +0.5f, +0.5f, Color[0], Color[1], Color[2]);

	//	Vertices.emplace_back(-0.5f, -0.5f, -0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(-0.5f, +0.5f, -0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(+0.5f, -0.5f, -0.5f, Color[0], Color[1], Color[2]);
	//	Vertices.emplace_back(+0.5f, +0.5f, -0.5f, Color[0], Color[1], Color[2]);

	//	Indices = {
	//		0, 1, 2, 2, 1, 3,
	//		6, 7, 4, 4, 7, 5,
	//		2, 3, 6, 6, 3, 7,
	//		4, 5, 0, 0, 5, 1,
	//		1, 5, 3, 3, 5, 7,
	//		4, 0, 6, 6, 0, 2
	//	};
	//}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexTexture), Vertices.size());
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

	DiffuseMap->Destroy();
}

void TestScene::Initialize()
{
	DiffuseMap = Texture::Add(L"Landscape/Box.png");
	//DiffuseMap = Texture::Add(L"../Datas/Textures/Color/Blue.png");
	//DiffuseMap = Texture::Add(L"../Datas/Textures/Block/Dirt.png");
	//DiffuseMap = Texture::Add(L"../Datas/Textures/HeightMaps/AlphaMap1.png");
	DiffuseMap->ReadPixels(Colors);
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
	DiffuseMap->PSSet(0);

	VShader->Set();
	PShader->Set();

	//D3D::GetDC()->Draw(Vertices.size(), 0);
	D3D::GetDC()->DrawIndexed(Indices.size(), 0, 0);
}

void TestScene::GUIRender()
{
	//ImGui::Begin("Test");
	//
	//TestObject->GUIRender();
	//
	//ImGui::End();

	ImGui::Begin("Test");

	string log = "";
	log += "FPS : " + to_string(1 / Time::Get()->GetDeltaTime());
	ImGui::Text(log.c_str());

	float pos[3];
	pos[0] = Pos.X;
	pos[1] = Pos.Y;
	pos[2] = Pos.Z;
	ImGui::DragFloat3("\nPosition", pos, 0.01f, -1.0f, 1.0f);
	Pos.X = pos[0];
	Pos.Y = pos[1];
	Pos.Z = pos[2];

	string debug = "";
	debug += "\nPos : " + Pos.ToString();
	ImGui::Text(debug.c_str());

	for (int i = 0; i < 4; i++)
	{
		string temp = "UV " + to_string(i);
		int x, y;
		x = Vertices[i].Uv.x;
		y = Vertices[i].Uv.y;
		ImGui::InputInt((temp + "_x").c_str(), &x);
		ImGui::InputInt((temp + "_y").c_str(), &y);
		Vertices[i].Uv.x = x;
		Vertices[i].Uv.y = y;

		ImGui::TextWrapped("");
	}

	if (ImGui::Button("Accept"))
	{
		VBuffer->Update(Vertices.data(), Vertices.size());
	}

	//ImGui::ColorEdit3("Color", Color);
	//Vertices[0].Color = {Color[0], Color[1], Color[2], 1.0f};
	//Vertices[1].Color = {Color[0], Color[1], Color[2], 1.0f};
	//Vertices[2].Color = {Color[0], Color[1], Color[2], 1.0f};
	//VBuffer->Update(Vertices.data(), Vertices.size());


	ImGui::End();
}
