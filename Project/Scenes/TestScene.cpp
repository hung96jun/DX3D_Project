#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"
#include "Objects/Environment/Grid.h"

TestScene::TestScene()
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(L"TestTextureShader");
	PShader = ShaderManager::Get()->AddPS(L"TestTextureShader");

	{
		// Front
		Vertices.emplace_back(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, -0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(+0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, -0.5f, 1.0f, 0.0f);
		
		// Back
		Vertices.emplace_back(+0.5f, -0.5f, +0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, +0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(-0.5f, -0.5f, +0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, +0.5f, 1.0f, 0.0f);

		// Left
		Vertices.emplace_back(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, -0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(-0.5f, -0.5f, +0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, +0.5f, 1.0f, 0.0f);

		// Right
		Vertices.emplace_back(+0.5f, -0.5f, +0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, +0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(+0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, -0.5f, 1.0f, 0.0f);

		// Top
		Vertices.emplace_back(+0.5f, +0.5f, +0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(+0.5f, +0.5f, -0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(-0.5f, +0.5f, +0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(-0.5f, +0.5f, -0.5f, 1.0f, 0.0f);

		// Top
		Vertices.emplace_back(-0.5f, -0.5f, +0.5f, 0.0f, 1.0f);
		Vertices.emplace_back(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
		Vertices.emplace_back(+0.5f, -0.5f, +0.5f, 1.0f, 1.0f);
		Vertices.emplace_back(+0.5f, -0.5f, -0.5f, 1.0f, 0.0f);

		Indices =
		{
			0, 1, 2, 2, 1, 3,
			4, 5, 6, 6, 5, 7,
			11, 9, 10, 10, 9, 8,
			15, 13, 14, 14, 13, 12,
			16, 17, 18, 18, 17, 19,
			20, 21, 22, 22, 21, 23
		};
	}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexUV), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));
	FBuffer = new FloatBuffer();
	WBuffer = new MatrixBuffer();

	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

TestScene::~TestScene()
{
	DESTRUCTOR_DEBUG();

	//SAFE_DELETE(TestObject);

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
	SAFE_DELETE(FBuffer);

	//DiffuseMap->Destroy();
	DiffuseMap[0]->Destroy();
	DiffuseMap[1]->Destroy();
}

void TestScene::Initialize()
{
	//DiffuseMap = Texture::Add(L"Color/White.png");
	DiffuseMap[0] = Texture::Add(L"Color/White.png");
	DiffuseMap[1] = Texture::Add(L"Color/White.png");
	//DiffuseMap[0] = Texture::Add(L"Landscape/Box.png");
	//DiffuseMap[1] = Texture::Add(L"Landscape/Bricks.png");
}

void TestScene::Destory()
{
}

void TestScene::Update()
{
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
	FBuffer->SetPS(3);
	
	//DiffuseMap->PSSet(0);
	DiffuseMap[0]->PSSet(0);
	DiffuseMap[1]->PSSet(1);

	VShader->Set();
	PShader->Set();

	//D3D::GetDC()->Draw(Vertices.size(), 0);
	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void TestScene::GUIRender()
{
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

	ImGui::DragFloat("Texture Ratio", &Ratio, 0.01f, 0.0f, 1.0f);
	FBuffer->Set(Ratio);

	if (ImGui::Button("Texture1"))
	{
		DIALOG->OpenDialog("LoadTexture1", "FindTexture", ".png,.dds,.jpg", "../Datas/Textures/");
	}

	if (DIALOG->Display("LoadTexture1"))
	{
		if (DIALOG->IsOk())
		{
			string str = DIALOG->GetFilePathName();
			size_t offset = str.rfind("Textures");
			if (offset != string::npos)
				offset += string("Textures").size() + 1;

			str = str.substr(offset);

			while (true) {
				size_t slashIndex = str.rfind("\\");
				if (slashIndex == std::string::npos) {
					break;
				}

				str.replace(slashIndex, 1, "/");
			}


			wstring path(str.begin(), str.end());
			DiffuseMap[0] = Texture::Add(path);

			DIALOG->Close();
		}
	}

	if (ImGui::Button("Texture2"))
	{
		DIALOG->OpenDialog("LoadTexture2", "FindTexture", ".png,.dds,.jpg", "../Datas/Textures/");
	}

	if (DIALOG->Display("LoadTexture2"))
	{
		if (DIALOG->IsOk())
		{
			string str = DIALOG->GetFilePathName();
			size_t offset = str.rfind("Textures");
			if (offset != string::npos)
				offset += string("Textures").size() + 1;

			str = str.substr(offset);

			while (true) {
				size_t slashIndex = str.rfind("\\");
				if (slashIndex == std::string::npos) {
					break;
				}

				str.replace(slashIndex, 1, "/");
			}


			wstring path(str.begin(), str.end());
			DiffuseMap[1] = Texture::Add(path);

			DIALOG->Close();
		}
	}

	ImGui::End();
}
