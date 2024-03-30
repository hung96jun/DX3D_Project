#pragma once

class Shader;
class VertexShader;
class PixelShader;

class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();

public:
	static ShaderManager* Get();
	static void Destroy();

	VertexShader* AddVS(wstring File);
	PixelShader* AddPS(wstring File);

private:
	static ShaderManager* Instance;
	static unordered_map<wstring, Shader*> Shaders;
};

