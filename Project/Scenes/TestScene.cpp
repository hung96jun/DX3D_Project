#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"

TestScene::TestScene()
{
	TestObject = new Object({ 0.0f, 0.0f }, { 0.3f, 0.3f });
}

TestScene::~TestScene()
{
	SAFE_DELETE(TestObject);
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
	TestObject->Render();
}

void TestScene::GUIRender()
{
	ImGui::Begin("Test");

	ImGui::End();
}
