#include "Box.h"
#include "Meshes/Shapes/BoxShape.h"

Box::Box()
{
	CONSTRUCTOR_DEBUG();

	Mesh = new BoxShape();
	
	Mesh->SetOwner(&Transform);

	SetTag("Box");
	Mesh->SetTag("Box");
	Mat->SetTag("Box");
}

Box::Box(const wstring ShaderFile)
{
	Mesh = new BoxShape(ShaderFile);
	Mesh->SetOwner(&Transform);

	SetTag("Box");
	Mesh->SetTag("Box");
	Mat->SetTag("Box");
}

Box::~Box()
{
	DESTRUCTOR_DEBUG();

}

void Box::Update()
{
	SUPER::Update();

	Mesh->Update();
}

void Box::Render()
{
	SUPER::Render();

	Mesh->Set();
	Mat->Set();

	Mesh->Render();
}

void Box::GUIRender()
{
	SUPER::GUIRender();
}
