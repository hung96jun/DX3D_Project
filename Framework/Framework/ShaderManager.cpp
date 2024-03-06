#include "Libraries.h"
#include "ShaderManager.h"
#include "Renders/Shader.h"
#include "Renders/Vertex.h"
#include "Renders/PixelShader.h"

ShaderManager* ShaderManager::Instance = nullptr;
unordered_map<wstring, Shader*> ShaderManager::Shaders;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

ShaderManager* ShaderManager::Get()
{
	if (Instance == nullptr)
	{
		Instance = new ShaderManager();
	}

	return Instance;
}

void ShaderManager::Delete()
{
	for (pair<wstring, Shader*> shader : Shaders)
		delete shader.second;
}

VertexShader* ShaderManager::AddVS(wstring File)
{
	if (File.size() == 0)
		File = L"";

	wstring key = File + L"VS";

	int* test;
	static_cast<float*>(static_cast<void*>(test));


	//if (Shaders.count(key) > 0)
	//	return static_cast<VertexShader*>(Shaders[key]);
	//
	//if (Shaders.count(key) > 0)
	//	return dynamic_cast<VertexShader*>(Shaders[key]);

	//if (Shaders.count(key) > 0)
	//	return (Vertexshader*)(Shaders[key]);


	return nullptr;
}

PixelShader* ShaderManager::AddPS(wstring File)
{
	return nullptr;
}
