#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(wstring File);
	~VertexShader();

	virtual void Set() override;

private:
	void CreateInputLayout();

public:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* InputLayout;
	ID3D11ShaderReflection* Reflection;
};