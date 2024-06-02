#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"

#include "Renders/Material.h"

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

	Mat = new Material(L"TestTextureShader");

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

	SAFE_DELETE(Mat);

	//DiffuseMap->Destroy();
	//DiffuseMap[0]->Destroy();
	//DiffuseMap[1]->Destroy();
}

void TestScene::Initialize()
{
	//DiffuseMap = Texture::Add(L"Color/White.png");
	//DiffuseMap[0] = Texture::Add(L"Color/White.png");
	//DiffuseMap[1] = Texture::Add(L"Color/White.png");
	//DiffuseMap[0] = Texture::Add(L"Landscape/Box.png");
	//DiffuseMap[1] = Texture::Add(L"Landscape/Bricks.png");

	Mat->SetDiffuseMap(L"Landscape/Box.png");
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
	WBuffer->Set(World);
	WBuffer->SetVS(0);
	VBuffer->Set();
	IBuffer->Set();
	FBuffer->SetPS(3);
	
	//DiffuseMap[0]->PSSet(0);
	//DiffuseMap[1]->PSSet(1);

	//VShader->Set();
	//PShader->Set();

	Mat->Set();

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

	if (ImGui::TreeNode("Material"))
	{
		float diffuse[4] = { Mat->GetData().Diffuse.x, Mat->GetData().Diffuse.y, Mat->GetData().Diffuse.z, Mat->GetData().Diffuse.w };
		float emissive[4] = { Mat->GetData().Emissive.x, Mat->GetData().Emissive.y, Mat->GetData().Emissive.z, Mat->GetData().Emissive.w };
		float ambient[4] = { Mat->GetData().Ambient.x, Mat->GetData().Ambient.y, Mat->GetData().Ambient.z, Mat->GetData().Ambient.w };
		float specular[4] = { Mat->GetData().Specular.x, Mat->GetData().Specular.y, Mat->GetData().Specular.z, Mat->GetData().Specular.w };

		ImGui::DragFloat4("Diffuse", diffuse, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat4("Specular", specular, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat4("Ambient", ambient, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat4("Emissive", emissive, 0.01f, 0.0f, 1.0f);
		
		Mat->GetData().Diffuse = Float4(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
		Mat->GetData().Specular = Float4(specular[0], specular[1], specular[2], specular[3]);
		Mat->GetData().Emissive = Float4(emissive[0], emissive[1], emissive[2], emissive[3]);
		Mat->GetData().Ambient = Float4(ambient[0], ambient[1], ambient[2], ambient[3]);

		ImGui::TreePop();
	}

	if (ImGui::Button("Texture"))
	{
		DIALOG->OpenDialog("LoadTexture1", "FindTexture", ".png,.dds,.jpg", "../Datas/Textures/");
	}

	if (DIALOG->Display("LoadTexture"))
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
			Mat->SetDiffuseMap(path);

			DIALOG->Close();
		}
	}

	ImGui::End();
}
