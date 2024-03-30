#include "Libraries.h"
#include "ShaderManager.h"
#include "Renders/Shaders/Shader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

ShaderManager* ShaderManager::Instance = nullptr;
unordered_map<wstring, Shader*> ShaderManager::Shaders;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	for (pair<wstring, Shader*> s : Shaders)
		SAFE_DELETE(s.second);
}

ShaderManager* ShaderManager::Get()
{
	if (Instance == nullptr)
		Instance = new ShaderManager();

	return Instance;
}

void ShaderManager::Destroy()
{
	SAFE_DELETE(Instance);
}

VertexShader* ShaderManager::AddVS(wstring File)
{
	if (File.size() == 0)
		File = L"";					// 베이스가 되는 shader 경로

	wstring key = File + L"VS";

	if (Shaders.count(key) > 0)
		return dynamic_cast<VertexShader*>(Shaders[key]);

	wstring path = L"../Framework/_Shaders/" + File;		// shader 폴더 경로 + shader 파일 이름.hlsl
	pair<wstring, Shader*> shaderPair;
	shaderPair.first = key;
	shaderPair.second = new VertexShader(path);
	Shaders.insert(shaderPair);

	return dynamic_cast<VertexShader*>(Shaders[key]);
}

PixelShader* ShaderManager::AddPS(wstring File)
{
	if (File.size() == 0)
		File = L"";					// 베이스가 되는 shader 경로

	wstring key = File + L"PS";

	if (Shaders.count(key) > 0)
		return dynamic_cast<PixelShader*>(Shaders[key]);

	wstring path = L"../Framework/_Shaders/" + File;		// shader 폴더 경로 + shader 파일 이름.hlsl
	pair<wstring, Shader*> shaderPair;
	shaderPair.first = key;
	shaderPair.second = new PixelShader(path);
	Shaders.insert(shaderPair);

	return dynamic_cast<PixelShader*>(Shaders[key]);
}
