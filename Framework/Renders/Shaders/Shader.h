#pragma once
#include "Libraries.h"
#include "Systems/D3D.h"

class Shader
{
public:
	Shader() = default;
	virtual ~Shader();

	virtual void Set() {}
	
protected:
	ID3DBlob* Blob;
};

