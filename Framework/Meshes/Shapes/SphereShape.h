#pragma once

#include "Shape.h"

class SphereShape : public Shape
{
public:
	SphereShape(const wstring ShaderFile = L"TestTextureShader");
	virtual ~SphereShape();

	virtual void Create() override;
	//virtual void Update() override;
	//virtual void Render() override;
	virtual void GUIRender() override;

	void Resize(const float Radius, const UINT StackCount, const UINT SliceCount)
	{
		this->Radius = Radius;
		this->StackCount = StackCount;
		this->SliceCount = SliceCount;

		Create();
	}

private:
	float Radius;

	UINT StackCount;
	UINT SliceCount;
};

