#pragma once

class Shader
{
public:
	Shader() = default;
	virtual ~Shader();

	virtual void Set() = 0;

protected:
	wstring File;
	ID3DBlob* Blob;
};