#include "stdafx.h"
#include "ModelInstanceScene.h"

/**
* Instancing을 하지 않고 Instnacing처럼 VertexBuffer로 넘길 정보에 Transform 정보도 포함시켜서
* 렌더 테스트 해보기
* TEST 2번을 추가해서
*/

void ModelInstanceScene::Initialize()
{
	//TestModel = new Model("Tank");
	//TestModel->ReadMesh(L"Tank/tank");
	//TestModel->ReadMaterial(L"Tank/tank");

	TestModel = new Model("Kachujin");
	TestModel->ReadMesh(L"Kachujin/Mesh");
	TestModel->ReadMaterial(L"Kachujin/Mesh");
	TestModel->SetMeshShader(L"ModelInstanceShader");
	TestModel->GetTransform().SetScale(Vector3(1.0f));
	TestModel->Update();

	//TestModel1 = new Model("Kachujin");
	//TestModel1->ReadMesh(L"Kachujin/Mesh");
	//TestModel1->ReadMaterial(L"Kachujin/Mesh");
	//TestModel1->SetMeshShader(L"ModelInstanceShader");
	//TestModel1->GetTransform().SetScale(Vector3(1.0f));
	//TestModel1->Update();

	for (int i = 0; i < Count; i++)
	{
		Transformation transform;
		transform.SetPosition(Vector3(i * 100.0f, 0.0f, 0.0f));
		transform.SetScale(Vector3(1.0f));

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
	TestModel->Update();
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
	TestModel->GUIRender("_0");
	//TestModel1->GUIRender("_1");
}
