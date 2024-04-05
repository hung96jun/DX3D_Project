#pragma once
#include "Libraries.h"
#include "Framework.h"
#include "Framework/Managers/ShaderManager.h"

class Object
{
public:
	Object(const wstring ShaderFile = L"SimpleShader");
	virtual ~Object();

	virtual void Update();
	virtual void PreRender() {}
	virtual void Render();
	virtual void PostRender() {}
	virtual void GUIRender() {}

private:
	VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;

protected:
	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	//WorldBuffer* WBuffer = nullptr;

	vector<VertexColor> Vertices;
	vector<UINT> Indices;

	Object* Owner = nullptr;
	Transformation Transform;
};
