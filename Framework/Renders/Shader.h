#pragma once

class Shader
{
public:
	Shader() = default;
	virtual ~Shader();

	virtual void Set() = 0;
	const wstring GetFile() const { return File; }

protected:
	wstring File;
	ID3DBlob* Blob;
};