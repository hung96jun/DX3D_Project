#pragma once

#include "Shape.h"

class QuadShape : public Shape
{
public:
	QuadShape(const wstring ShaderFile = L"TestTextureShader");
	virtual ~QuadShape();

	virtual void Create() override;
	virtual void GUIRender() override;

	void Resize(const Vector2 Size)
	{
		this->Size = Size;
		Create();
	}

private:
	Vector2 Size;
};