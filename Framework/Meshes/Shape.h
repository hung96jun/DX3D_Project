#pragma once

#include "Libraries.h"
#include "Framework.h"

class Shape
{
public:
	Shape(const wstring ShaderFile = L"TestTextureShader");
	virtual ~Shape();

	virtual void Create() = 0;
	virtual void GUIRender();

	void Update();
	void Render();

	void Set();

	void SetPosition(const Vector3 Pos);
	void SetRotation(const Vector3 Rot);
	void SetScale(const Vector3 Scale);

	void AddPosition(const Vector3 Pos);
	void AddRotation(const Vector3 Rot);
	void AddScale(const Vector3 Scale);

	void SetVertices(vector<VertexMesh> Vertices, vector<UINT> Indices = vector<UINT>());

	void SetTag(const string Tag) { Transform.SetTag(Tag + "_Mesh"); }
	void SetOwner(Transformation* OwnTransform) { Transform.SetOwner(OwnTransform); }

	void SetHidden(const bool Value) { bHidden = Value; }
	const bool& IsHidden() { return bHidden; }

	const int GetIndicesSize() { return static_cast<int>(Indices.size()); }

protected:
	void Resize();

protected:
	Transformation Transform;

private:
	VertexShader* VShader = nullptr;

	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	vector<VertexMesh> Vertices;
	vector<UINT> Indices;

	bool bHidden = false;
	bool bSet = false;
};

