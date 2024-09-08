#include "stdafx.h"
#include "ModelScene.h"

/**
* Instancing�� ���� �ʰ� Instnacingó�� VertexBuffer�� �ѱ� ������ Transform ������ ���Խ��Ѽ�
* ���� �׽�Ʈ �غ���
* TEST 2���� �߰��ؼ�
*/

void ModelScene::Initialize()
{
	TestModel = new Model("Tank");
	TestModel->ReadMesh(L"Tank/tank");
	TestModel->ReadMaterial(L"Tank/tank");

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
