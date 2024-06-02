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
	virtual void GUIRender();

	void SetTag(const string Tag) { Transform.SetTag(Tag); }
	const string& GetTag() const { return Transform.GetTag(); }

private:
	VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;

protected:
	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	vector<VertexColor> Vertices;
	vector<UINT> Indices;

	Object* Owner = nullptr;
	Transformation Transform;
};
