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

	void SetShader(const wstring ShaderFile);
	void SetDiffuseMap(const wstring TextureFile);
	void SetSpecularMap(const wstring TextureFile);
	void SetNormalMap(const wstring TextureFile);

	Texture* GetDiffuseMap() { return DiffuseMap; }
	Texture* GetSpecularMap() { return SpecularMap; }
	Texture* GetNormalMap() { return NormalMap; }

	void SetDiffuseMap(Texture* DiffuseMap) { this->DiffuseMap = DiffuseMap; }
	void SetSpecularMap(Texture* SpecularMap) { this->SpecularMap = SpecularMap; }
	void SetNormalMap(Texture* NormalMap) { this->NormalMap = NormalMap; }

	const wstring& GetDiffuseFile() const { return DiffuseFile; }
	const wstring& GetSpecularFile() const { return SpecularFile; }
	const wstring& GetNormalFile() const { return NormalFile; }

	void SetDiffuseFile(const wstring& Path) { DiffuseFile = Path; }
	void SetSpecularFile(const wstring& Path) { SpecularFile = Path; }
	void SetNormalFile(const wstring& Path) { NormalFile = Path; }

	void Save(string File);
	void Load(string File);

	const string& GetTag() const { return Tag; }
	void SetTag(const string Name) { this->Tag = Name; }
	MaterialBuffer::BufferData& GetData() { return MBuffer->Get(); }

	void SetAmbient(const Color Value) { Ambient = Value; }
	void SetDiffuse(const Color Value) { Diffuse = Value; }
	void SetSpecular(const Color Value) { Specular = Value; }
	void SetEmissive(const Color Value) { Emissive = Value; }

	const Color& GetAmbient() const { return Ambient; }
	const Color& GetDiffuse() const { return Diffuse; }
	const Color& GetSpecular() const { return Specular; }
	const Color& GetEmissive() const { return Emissive; }

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

	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	wstring DiffuseFile;
	wstring SpecularFile;
	wstring NormalFile;

	Texture* DiffuseMap = nullptr;
	Texture* SpecularMap = nullptr;
	Texture* NormalMap = nullptr;

	MaterialBuffer* MBuffer = nullptr;
};

