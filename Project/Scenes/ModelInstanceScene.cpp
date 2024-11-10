#include "stdafx.h"
#include "ModelInstanceScene.h"

/**
* Instancing�� ���� �ʰ� Instnacingó�� VertexBuffer�� �ѱ� ������ Transform ������ ���Խ��Ѽ�
* ���� �׽�Ʈ �غ���
* TEST 2���� �߰��ؼ�
*/

void ModelInstanceScene::Initialize()
{
	TestModel = new Model("Kachujin");
	TestModel->ReadMesh(L"Kachujin/Mesh");
	TestModel->ReadMaterial(L"Kachujin/Mesh");
	TestModel->SetMeshShader(L"ModelInstanceShader");

	for (int i = 0; i < Count; i++)
	{
		Transformation transform;
		transform.SetPosition(Vector3(i * 20.0f, 0.0f, 0.0f));
		transform.SetScale(Vector3(0.1f));

		transform.Update();

		Transforms.push_back(transform);
		Instances.push_back(transform.GetWorld());
	}

	InstanceBuffer = new VertexBuffer(Instances.data(), sizeof(Matrix), Count);
}

void ModelInstanceScene::Destroy()
{
	SAFE_DELETE(TestModel);
	//SAFE_DELETE(TestModel1);
}

void ModelInstanceScene::Update()
{
	//TestModel->Update();
	//TestModel1->Update();

	transform(Transforms.begin(), Transforms.end(), Instances.data(),
		[](Transformation t)
		{
			t.Update();
			return t.GetWorld();
		});
}

void ModelInstanceScene::Render()
{
	InstanceBuffer->Update(Instances.data(), Count);
	InstanceBuffer->Set(1);

	TestModel->Render(Count);
	//TestModel1->Render();
}

void ModelInstanceScene::GUIRender()
{
	//TestModel->GUIRender("_0");
	//TestModel1->GUIRender("_1");

	if (ImGui::TreeNode("Instance Transform"))
	{
		for (int i = 0; i < Transforms.size(); i++)
		{
			if (ImGui::TreeNode((to_string(i) + "_Instance").c_str()))
			{
				Transforms[i].GUIRender();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}
