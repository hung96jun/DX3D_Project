#include "stdafx.h"
#include "ModelScene.h"

/**
* Instancing을 하지 않고 Instnacing처럼 VertexBuffer로 넘길 정보에 Transform 정보도 포함시켜서
* 렌더 테스트 해보기
* TEST 2번을 추가해서
*/

void ModelScene::Initialize()
{
	//TestModel = new Model("Tank");
	//TestModel->ReadMesh(L"Tank/tank");
	//TestModel->ReadMaterial(L"Tank/tank");

	TestModel = new Model("Kachujin");
	TestModel->ReadMesh(L"Kachujin/Mesh");
	TestModel->ReadMaterial(L"Kachujin/Mesh");

	TestModel->Update();
}

void ModelScene::Destroy()
{
	SAFE_DELETE(TestModel);
}

void ModelScene::Update()
{
	TestModel->Update();
}

void ModelScene::Render()
{
	TestModel->Render();
}

void ModelScene::GUIRender()
{
	TestModel->GUIRender();
}
