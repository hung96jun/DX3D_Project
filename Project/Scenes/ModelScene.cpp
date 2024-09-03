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
	TestModel->Update();
}

void ModelScene::Destory()
{
	SAFE_DELETE(TestModel);
}

void ModelScene::Update()
{
}

void ModelScene::Render()
{
	TestModel->Render();
}

void ModelScene::GUIRender()
{
}
