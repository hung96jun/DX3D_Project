#pragma once

#include "Shape.h"

class BoxShape : public Shape
{
public:
	BoxShape(const wstring ShaderFile = L"TestTextureShader");
	~BoxShape();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;

private:
	float X, Y, Z;
};