#pragma once
//#include "Framework.h"
#include <DirectXMath.h>

struct Color
{
public:
	Color() : R(0.0f), G(0.0f), B(0.0f), A(0.0f) {}
	Color(float r, float g, float b, float a = 1.0f) : R(r), G(g), B(b), A(a) {}
	//Color(Float4 color) : R(color.x), G(color.y), B(color.z), A(color.w) {}

	operator DirectX::XMFLOAT4() { return DirectX::XMFLOAT4(R, G, B, A); }

	static const Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
	static const Color Blue() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
	static const Color Green() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }

public:
	float R;
	float G;
	float B;
	float A;
};