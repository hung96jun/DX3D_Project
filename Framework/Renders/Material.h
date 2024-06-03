#pragma once
#include "Framework/Buffers/GlobalBuffer.h"


class VertexShader;
class PixelShader;
class Texture;

enum class MapType
{
	DIFFUSE, SPECULAR, NORMAL
};

class Material
{
public:
	Material(const wstring ShaderFile = L"TestTextureShader");
	~Material();

	void Set();

	void GUIRender();

	//void SetShader(const wstring ShaderFile);
	void SetDiffuseMap(const wstring TextureFile);
	void SetSpecularMap(const wstring TextureFile);
	void SetNormalMap(const wstring TextureFile);

	void Save(string File);
	void Load(string File);

	const string& GetTag() const { return Tag; }
	void SetTag(const string Name) { this->Tag = Name; }
	MaterialBuffer::BufferData& GetData() { return MBuffer->Get(); }

private:
	void Initializer();

	void SelectMap(const string Name, const MapType Type);
	void UnSelectMap(const MapType Type);

	void SaveDialog();
	void LoadDialog();

private:
	string Tag;
	string EditNamt;
	string File;
	string ProjectPath;

	//VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;

	Texture* DiffuseMap = nullptr;
	Texture* SpecularMap = nullptr;
	Texture* NormalMap = nullptr;

	MaterialBuffer* MBuffer = nullptr;
};

