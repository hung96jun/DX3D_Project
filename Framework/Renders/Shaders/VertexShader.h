#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader() = default;
	VertexShader(wstring File);
	virtual ~VertexShader();

	virtual void Set() override;

private:
	ID3D11VertexShader* VShader = nullptr;
	ID3D11InputLayout* InputLayout = nullptr;
};
