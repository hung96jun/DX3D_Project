#include "stdafx.h"
#include "TextureScene.h"
#include "Objects/TestObject.h"
#include "Environment/Terrain.h"

TextureScene::TextureScene()
{
	CONSTRUCTOR_DEBUG();

	Object[0] = new TestObject(0);
	Object[1] = new TestObject(1);

	Field = new Terrain(125, 125, L"Block/Dirt.png");
}

TextureScene::~TextureScene()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Object[0]);
	SAFE_DELETE(Object[1]);

	SAFE_DELETE(Field);
}

void TextureScene::Initialize()
{
}

void TextureScene::Destory()
{
}

void TextureScene::Update()
{
	Object[0]->Update();
	Object[1]->Update();
}

void TextureScene::Render()
{
	Object[0]->Render();
	Object[1]->Render();

	Field->Render();
}

void TextureScene::GUIRender()
{
	Object[0]->GUIRender();
	Object[1]->GUIRender();

	//if (ImGui::Button("SaveDepthTexture"))
	//{
	//	D3D::Get()->DepthTest();
	//}

	Field->GUIRender();
}
