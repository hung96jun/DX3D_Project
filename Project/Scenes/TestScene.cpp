#include "stdafx.h"
#include "TestScene.h"
#include "Objects/Object.h"

TestScene::TestScene()
{
	TestObject = new Object({ 0.0f, 0.0f }, { 0.5f, 0.5f });
}

TestScene::~TestScene()
{
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

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	TestObject->Render();
}

void TestScene::PostRender()
{
}

void TestScene::ResizeScreen()
{
}

void TestScene::GUIRender()
{
}

void TestScene::Disable()
{
}
