#include "stdafx.h"
#include "TextureScene.h"
#include "Objects/TestObject.h"
#include "Environment/Terrain.h"
#include "Managers/InstanceManager.h"

#include "Objects/Base/Box.h"

TextureScene::TextureScene()
{
	CONSTRUCTOR_DEBUG();

	//Object[0] = new TestObject(0);
	//Object[1] = new TestObject(1);

#if INSTANCE_TEST == 0
	Object = new Box();
#endif //  

#if INSTANCE_TEST == 1
	for (int i = 0; i < 10; i++)
	{
		Box* obj = new Box(L"TestInstanceShader");
		Objects.push_back(obj);
		InstanceManager::Get()->Push(&obj->GetTransform());

		Vector3 rand = Math::RandomVector3(50, 10);
		obj->GetTransform().SetPosition(rand);
		rand = Math::RandomVector3(5, 1);
		obj->GetTransform().SetScale(rand);
	}
#endif

	Field = new Terrain(125, 125, L"Block/Dirt.png");
}

TextureScene::~TextureScene()
{
	DESTRUCTOR_DEBUG();

	//SAFE_DELETE(Object[0]);
	//SAFE_DELETE(Object[1]);

#if INSTANCE_TEST == 0
	SAFE_DELETE(Object);
#endif

#if INSTANCE_TEST == 1
	for (Box* b : Objects)
		SAFE_DELETE(b);
#endif

	SAFE_DELETE(Field);

	InstanceManager::Destroy();
}

void TextureScene::Initialize()
{
}

void TextureScene::Destory()
{
}

void TextureScene::Update()
{
	//Object[0]->Update();
	//Object[1]->Update();
	
#if INSTANCE_TEST == 0
	Object->Update();
#endif

#if INSTANCE_TEST == 1
	for (Box* b : Objects)
		b->Update();
#endif // 

}

void TextureScene::Render()
{
	//Object[0]->Render();
	//Object[1]->Render();
	//Object->Render();

#if  INSTANCE_TEST == 0
	Object->Render();
#endif //  INSTANCE_TEST == 0


#if INSTANCE_TEST == 1
	Objects[0]->Render();

	//for (Box* b : Objects)
	//	b->Render();

	InstanceManager::Get()->Render();
#endif // INSTANCE_TEST == 1


	Field->Render();
}

void TextureScene::GUIRender()
{
	//Object[0]->GUIRender();
	//Object[1]->GUIRender();

	//if (ImGui::Button("SaveDepthTexture"))
	//{
	//	D3D::Get()->DepthTest();
	//}

	//ImGui::Begin("Debug");

	{
		string debug = "";
		debug = "FPS : " + to_string(Time::Get()->GetFPS());
		ImGui::Text(debug.c_str());
	}

	//ImGui::End();

#if INSTANCE_TEST == 0
	Object->GUIRender();
#endif

	Field->GUIRender();
}
