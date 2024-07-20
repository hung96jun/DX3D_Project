#pragma once
#include "../Shape.h"

class CylinderShape : public Shape
{
public:
	CylinderShape(const wstring ShaderFile = L"TestTextureShader");
	~CylinderShape();

	virtual void Create() override;
	virtual void GUIRender() override;

	void Resize(const float TopRadius, const float BottomRadius, const float Height, const UINT StackCount, const UINT SliceCount)
	{
		this->TopRadius = TopRadius;
		this->BottomRadius = BottomRadius;
		this->Height = Height;
		this->StackCount = StackCount;
		this->SliceCount = SliceCount;
		Create();
	}

private:
	void TopCap(vector<VertexMesh>& Vertices, vector<UINT>& Indices);
	void BottomCap(vector<VertexMesh>& Vertices, vector<UINT>& Indices);

private:
	float TopRadius;
	float BottomRadius;
	float Height;

	UINT StackCount;
	UINT SliceCount;
};

