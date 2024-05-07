#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader() = delete;
	VertexShader(wstring File);
	virtual ~VertexShader();

	virtual void Set() override;

private:
	void CreateInputLayout();

private:
	ID3D11VertexShader* VShader = nullptr;
	ID3D11InputLayout* InputLayout = nullptr;

	ID3D11ShaderReflection* Reflection;
};

