#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(wstring File);
	~VertexShader();

	virtual void Set() override;

public:

};