#include "stdafx.h"
#include "LightScene.h"
#include "Objects/TestObject.h"
#include "Environment/Terrain.h"
#include "Managers/InstanceManager.h"

#include "Objects/Base/Box.h"

LightScene::LightScene()
{
	CONSTRUCTOR_DEBUG();

	Object = new Box();
	Object->GetMaterial()->SetNormalMap(L"Landscape/Fieldstone_NM.tga");
	Object->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	Object->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");

	Light = new Box();

	LBuffer = new LightBuffer();

	Field = new Terrain(125, 125);
	Field->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt3.png");
}

LightScene::~LightScene()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Object);
	SAFE_DELETE(Field);
	SAFE_DELETE(LBuffer);

	SAFE_DELETE(Light);
}

void LightScene::Initialize()
{
	//Field->GetTransform().SetPosition(Vector3(-62.5f, 0.0f, -62.5f));
	//Field->GetTransform().Update();
}

void LightScene::Destroy()
{
}

void LightScene::Update()
{
	Object->Update();

	Light->GetTransform().SetPosition(LightDesc.Position);
	Light->GetTransform().SetRotation(LightDesc.Direction);
	Light->Update();
}

void LightScene::Render()
{
	LBuffer->Get() = LightDesc;
	LBuffer->SetPS(3);

	Object->Render();

	Field->Render();

	Light->Render();
}

void LightScene::GUIRender()
{
	{
		string debug = "";
		debug = "FPS : " + to_string(Time::Get()->GetFPS());
		ImGui::Text(debug.c_str());
	}

	if (ImGui::TreeNode("Light"))
	{
		float temp[4];
		temp[0] = LightDesc.Ambient.R;
		temp[1] = LightDesc.Ambient.G;
		temp[2] = LightDesc.Ambient.B;
		temp[3] = LightDesc.Ambient.A;
		ImGui::DragFloat4("Ambient", temp, 0.01f, 0.0f, 1.0f);
		//LightDesc.Ambient = Vector4(temp[0], temp[1], temp[2], temp[3]);
		LightDesc.Ambient = temp;

		temp[0] = LightDesc.Diffuse.R;
		temp[1] = LightDesc.Diffuse.G;
		temp[2] = LightDesc.Diffuse.B;
		temp[3] = LightDesc.Diffuse.A;
		ImGui::DragFloat4("Diffuse", temp, 0.01, 0.0f, 1.0f);
		//LightDesc.Diffuse = Vector4(temp[0], temp[1], temp[2], temp[3]);
		LightDesc.Diffuse = temp;

		temp[0] = LightDesc.Specular.R;
		temp[1] = LightDesc.Specular.G;
		temp[2] = LightDesc.Specular.B;
		temp[3] = LightDesc.Specular.A;
		ImGui::DragFloat4("Specular", temp, 0.01, 0.0f, 1.0f);
		//LightDesc.Specular = Vector4(temp[0], temp[1], temp[2], temp[3]);
		LightDesc.Specular = temp;

		float temp1[3];
		temp1[0] = LightDesc.Direction.X;
		temp1[1] = LightDesc.Direction.Y;
		temp1[2] = LightDesc.Direction.Z;
		//ImGui::DragFloat3("Direction", temp1, 0.001f, -1.0f, 1.0f);
		ImGui::DragFloat3("Direction", temp1, 0.001f);
		//LightDesc.Direction = Vector3(temp1[0], temp1[1], temp1[2]);
		LightDesc.Direction = temp1;

		temp1[0] = LightDesc.Position.X;
		temp1[1] = LightDesc.Position.Y;
		temp1[2] = LightDesc.Position.Z;
		ImGui::DragFloat3("Position", temp1, 0.01f);
		//LightDesc.Position = Vector3temp1[0], temp1[1], temp1[2]);
		LightDesc.Position = temp1;

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Terrain"))
	{
		float temp[3];
		Vector3 pos = Field->GetTransform().GetPosition();
		temp[0] = pos.X;
		temp[1] = pos.Y;
		temp[2] = pos.Z;
		ImGui::DragFloat3("Position", temp, 0.1f);
		pos = temp;
		Field->GetTransform().SetPosition(pos);
		Field->GetTransform().Update();

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Test"))
	{
		string temp = "Mouse : ";
		if (Mouse::Get()->IsDown(VK_LBUTTON) == true)
			ImGui::Text((temp + "LButton").c_str());
		if (Mouse::Get()->IsDown(VK_RBUTTON) == true)
			ImGui::Text((temp + "RButton").c_str());
		if (Mouse::Get()->IsDown(VK_MBUTTON) == true)
			ImGui::Text((temp + "MButton").c_str());
		if (Mouse::Get()->IsDown(VK_XBUTTON1) == true)
			ImGui::Text((temp + "XButton1").c_str());
		if (Mouse::Get()->IsDown(VK_XBUTTON2) == true)
			ImGui::Text((temp + "XButton2").c_str());

		temp = "Pos : ";
		ImGui::Text((temp + Mouse::Get()->GetMouseMoveValue().ToString()).c_str());

		temp = "Wheeel : ";
		ImGui::Text((temp + to_string(Mouse::Get()->GetMouseWheel())).c_str());
		//if(Mouse::GetMouseWheel() )

		ImGui::TreePop();
	}

	Object->GUIRender();
	Field->GUIRender();
}
