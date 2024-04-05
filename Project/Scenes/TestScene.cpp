#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"
#include "Objects/Environment/Grid.h"

TestScene::TestScene()
{
	//TestObject = new Object({ 0.0f, 0.0f }, { 0.3f, 0.3f });
	TestGrid = new Grid();
}

TestScene::~TestScene()
{
	SAFE_DELETE(TestGrid);
}

void TestScene::Initialize()
{
}

void TestScene::Destory()
{
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	TestGrid->Render();
}

void TestScene::GUIRender()
{
	ImGui::Begin("Test");

	ImGui::End();
}
