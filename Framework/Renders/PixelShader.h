#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader(wstring File);
	~PixelShader();

	virtual void Set() override;
};