#pragma once
#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader() = default;
	PixelShader(wstring File);
	~PixelShader();

	virtual void Set() override;

private:
	ID3D11PixelShader* PShader = nullptr;
};

