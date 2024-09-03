#include "stdafx.h"
#include "ModelScene.h"

/**
* Instancing을 하지 않고 Instnacing처럼 VertexBuffer로 넘길 정보에 Transform 정보도 포함시켜서
* 렌더 테스트 해보기
* TEST 2번을 추가해서
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
