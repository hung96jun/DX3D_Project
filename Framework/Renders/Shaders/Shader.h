#pragma once
#include "Libraries.h"
#include "Systems/D3D.h"
#include "Utilities/Debug.h"

class Shader
{
public:
	Shader() = delete;
	Shader(const wstring File);
	virtual ~Shader();

	virtual void Set() {}

	const wstring GetFile() const { return File; }
	
protected:
	wstring File;
	ID3DBlob* Blob;
};

