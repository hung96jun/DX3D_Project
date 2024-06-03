#include "stdafx.h"
#include "TestObject.h"
#include "Meshes/BoxShape.h"

TestObject::TestObject(const int Index)
	:Index(Index)
{
	CONSTRUCTOR_DEBUG();

	Mesh = new BoxShape(L"TestTextureShader");
	Mesh->SetOwner(&Transform);
	
	WBuffer = new MatrixBuffer();

	Mat = new Material(L"TestTextureShader");

	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

TestObject::~TestObject()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Mesh);
	SAFE_DELETE(WBuffer);

	SAFE_DELETE(Mat);
}

void TestObject::Update()
{
	Transform.SetPosition(Pos);
	Transform.SetRotation(Rot);
	Transform.SetScale(Scale);

	Transform.Update();

	Mesh->Update();
}

void TestObject::Render()
{
	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	Mesh->Set();
	Mat->Set();

	Mesh->Render();
}

void TestObject::GUIRender()
{
	if (ImGui::Begin("Objects"))
	{
		if(ImGui::TreeNode(("Object_" + to_string(Index)).c_str()))
		{
			float pos[3];
			pos[0] = Pos.X;
			pos[1] = Pos.Y;
			pos[2] = Pos.Z;
			ImGui::DragFloat3("Position", pos, 0.01f);
			Pos = pos;

			float rot[3];
			rot[0] = Rot.X;
			rot[1] = Rot.Y;
			rot[2] = Rot.Z;

			ImGui::DragFloat3("Rotation", rot, 0.01f);
			Rot = rot;

			float scale[3];
			scale[0] = Scale.X;
			scale[1] = Scale.Y;
			scale[2] = Scale.Z;

			ImGui::DragFloat3("Scale", scale, 0.01f);
			Scale = scale;

			if (ImGui::Button(("Texture" + to_string(Index)).c_str()))
			{
				DIALOG->OpenDialog("LoadTexture" + to_string(Index), "FindTexture", ".png,.dds,.jpg", "../Datas/Textures/");
			}

			if (DIALOG->Display("LoadTexture" + to_string(Index)))
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

			ImGui::TreePop();
		}

		ImGui::End();
	}
}
