#pragma once

class ShaderBase
{
protected:
	ShaderBase();
	virtual ~ShaderBase();

	static void Create();
	static void Delete();

	wstring GetFile() { return FileName; }

private:
	static ShaderBase* Instance;

	wstring FileName;
	ID3DBlob* Blob;
	static unordered_map<wstring, ShaderBase*> Shaders;
};

