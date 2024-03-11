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
	static void Delete();

	static VertexShader* AddVS(wstring File);
	static PixelShader* AddPS(wstring File);

private:
	static ShaderManager* Instance;
	
	static unordered_map<wstring, Shader*> Shaders;
};