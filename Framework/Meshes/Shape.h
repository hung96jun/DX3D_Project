#pragma once

#include "Libraries.h"
#include "Framework.h"

class Shape
{
public:
	Shape(const wstring ShaderFile = L"TestTextureShader");
	virtual ~Shape();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void Set();

	void SetPosition(const Vector3 Pos);
	void SetRotation(const Vector3 Rot);
	void SetScale(const Vector3 Scale);

	void AddPosition(const Vector3 Pos);
	void AddRotation(const Vector3 Rot);
	void AddScale(const Vector3 Scale);

	void SetVertices(vector<VertexMesh> Vertices, vector<int> Indices);
	void SetTag(const string Tag) { Transform.SetTag(Tag); }
	void SetOwner(Transformation* OwnTransform) { Transform.SetParent(OwnTransform); }
	
	void SetHidden(const bool Value) { bHidden = Value; }
	const bool IsHidden() const { return bHidden; }

private:
	VertexShader* VShader = nullptr;

	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	vector<VertexMesh> Vertices;
	vector<int> Indices;

	bool bHidden = false;
	bool bSet = false;

protected:
	Transformation Transform;
};