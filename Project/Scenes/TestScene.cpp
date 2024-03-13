#include "stdafx.h"
#include "TestScene.h"

void TestScene::Initializer()
{
	Test = new Object(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f));
}

void TestScene::Destroy()
{
	SAFE_DELETE(Test);
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	Test->Render();
}
