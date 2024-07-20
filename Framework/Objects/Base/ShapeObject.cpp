#include "ShapeObject.h"
#include "Meshes/Shape.h"

ShapeObject::ShapeObject()
{
	CONSTRUCTOR_DEBUG();

	//Mesh = new BoxShape();
	Mat = new Material();
}

ShapeObject::~ShapeObject()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Mesh);
	SAFE_DELETE(Mat);
}

void ShapeObject::Initialize()
{
	if (Mesh != nullptr)
		Mesh->SetOwner(&Transform);
}

void ShapeObject::Update()
{
	SUPER::Update();

	if (Mesh == nullptr) return;
	
	Mesh->Update();
}

void ShapeObject::Render()
{
	SUPER::Render();

	if (Mesh == nullptr) return;

	Mesh->Set();
	Mat->Set();

	Mesh->Render();
}

void ShapeObject::GUIRender()
{
	SUPER::GUIRender();

	if (Mesh == nullptr) return;

	Mesh->GUIRender();
	Mat->GUIRender();
}

void ShapeObject::SetTag(const string Tag)
{
	SUPER::SetTag(Tag);

	Mesh->SetTag(Tag);
	Mat->SetTag(Tag);
}
