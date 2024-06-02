#pragma once

#include "Libraries.h"
#include "Framework.h"

class Mesh
{
public:
	Mesh(const wstring VertexShader);
	virtual ~Mesh();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetPosition(const Vector3 Pos);
	void SetRotation(const Vector3 Rot);
	void SetScale(const Vector3 Scale);

	void AddPosition(const Vector3 Pos);
	void AddRotation(const Vector3 Rot);
	void AddScale(const Vector3 Scale);

	void SetVertices(vector<VertexMesh> Vertices, vector<int> Indices);

private:
	VertexShader* VShader = nullptr;
	//PixelShader* PShader = nullptr;

	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	vector<VertexMesh> Vertices;
	vector<int> Indices;

protected:
	Transformation Transform;
};