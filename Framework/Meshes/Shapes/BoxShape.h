#pragma once
#include "../Shape.h"

class BoxShape : public Shape
{
public:
	BoxShape(const wstring ShaderFile = L"TextureShader");
	~BoxShape();

	void Create() override;
	//virtual void Update() override;
	//virtual void Render() override;
	virtual void GUIRender() override;

	void Resize(const Vector3 Size)
	{
		X = Size.X;
		Y = Size.Y;
		Z = Size.Z;

		Create();
	}

private:
	float X, Y, Z;
};