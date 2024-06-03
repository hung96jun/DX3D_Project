#pragma once
#include "Libraries.h"
#include "Framework.h"
#include "Framework/Managers/ShaderManager.h"

#include "Object.h"

class Actor : public Object
{
public:
	Actor(const wstring ShaderFile = L"SimpleShader");
	virtual ~Actor();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender()  override {}
	virtual void Render() override;
	virtual void PostRender()  override {}
	virtual void GUIRender() override;

	virtual void SetTag(const string Tag) { Transform.SetTag(Tag); }
	const string& GetTag() const { return Transform.GetTag(); }

	const Transformation& GetTransform() { return Transform; }

private:
	//VertexShader* VShader = nullptr;
	//PixelShader* PShader = nullptr;

protected:
	//VertexBuffer* VBuffer = nullptr;
	//IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	//vector<VertexColor> Vertices;
	//vector<UINT> Indices;

	Actor* Owner = nullptr;
	Transformation Transform;
};
