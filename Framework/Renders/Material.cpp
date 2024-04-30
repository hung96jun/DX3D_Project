#include "Libraries.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Framework/Managers/ShaderManager.h"
#include "Framework/Buffers/GlobalBuffer.h"
#include "Renders/Texture.h"
#include "Utilities/tinyxml2.h"
#include "Utilities/Utility.h"
#include "Material.h"

Material::Material()
{
	Initializer();
}

Material::Material(const wstring ShaderFile)
{
	VShader = ShaderManager::Get()->AddVS(ShaderFile);
	PShader = ShaderManager::Get()->AddPS(ShaderFile);

	Initializer();
}

void Material::Initializer()
{
	DiffuseMap = Texture::Add(L"Color/White.png", L"DM");
	SpecularMap = Texture::Add(L"Color/White.png", L"SM");
	NormalMap = Texture::Add(L"Color/White.png", L"NM");

	MBuffer = new MaterialBuffer();

	char path[128];
	GetCurrentDirectoryA(128, path);
	ProjectPath = path;
}

Material::~Material()
{
	SAFE_DELETE(MBuffer);
}

void Material::Set()
{
	DiffuseMap->PSSet(0);
	SpecularMap->PSSet(1);
	NormalMap->PSSet(2);

	MBuffer->SetPS(1);

	VShader->Set();
	PShader->Set();
}

//void Material::SetShader(const wstring ShaderFile)
//{
//}

void Material::SetDiffuseMap(const wstring TextureFile)
{
	if (TextureFile.length() > 0)
		DiffuseMap = Texture::Add(TextureFile);
	else
		DiffuseMap = Texture::Add(L"Color/White.png", L"DM");
}

void Material::SetSpecularMap(const wstring TextureFile)
{
	if (TextureFile.length() > 0)
		SpecularMap = Texture::Add(TextureFile);
	else
		SpecularMap = Texture::Add(L"Color/White.png", L"SM");
}

void Material::SetNormalMap(const wstring TextureFile)
{
	if (TextureFile.length() > 0)
		NormalMap = Texture::Add(TextureFile);
	else
		NormalMap = Texture::Add(L"Color/White.png", L"NM");
}

void Material::SelectMap(const string Name, const MapType Type)
{
}

void Material::UnSelectMap(const MapType Type)
{
}

void Material::Save(string File)
{
	TXML::XMLDocument* document = new TXML::XMLDocument();
	TXML::XMLElement* material = document->NewElement("Material");
	material->SetAttribute("Name", Name.c_str());
	document->InsertFirstChild(material);

	TXML::XMLElement* shader = document->NewElement("Shader");
	string shaderFile;
	if (VShader != nullptr)
		shaderFile = ToString(VShader->GetFile());
	shader->SetAttribute("Vertex", shaderFile.c_str());

	if (PShader != nullptr)
		shaderFile = ToString(PShader->GetFile());
	shader->SetAttribute("Pixel", shaderFile.c_str());
	material->InsertFirstChild(shader);

	TXML::XMLElement* texture = document->NewElement("Texture");
	string textureFile;
	textureFile = ToString(DiffuseMap->GetFile());
	texture->SetAttribute("Diffuse", textureFile.c_str());
	textureFile = ToString(SpecularMap->GetFile());
	texture->SetAttribute("Specular", textureFile.c_str());
	textureFile = ToString(NormalMap->GetFile());
	texture->SetAttribute("Normal", textureFile.c_str());
	material->InsertEndChild(texture);
	
	TXML::XMLElement* property = document->NewElement("Property");
	TXML::XMLElement* diffuse = document->NewElement("Diffuse");
	diffuse->SetAttribute("R", MBuffer->Get().Diffuse.x);
	diffuse->SetAttribute("G", MBuffer->Get().Diffuse.y);
	diffuse->SetAttribute("B", MBuffer->Get().Diffuse.z);
	diffuse->SetAttribute("A", MBuffer->Get().Diffuse.w);
	property->InsertEndChild(diffuse);

	TXML::XMLElement* specular = document->NewElement("Specular");
	specular->SetAttribute("R", MBuffer->Get().Specular.x);
	specular->SetAttribute("G", MBuffer->Get().Specular.y);
	specular->SetAttribute("B", MBuffer->Get().Specular.z);
	specular->SetAttribute("A", MBuffer->Get().Specular.w);
	property->InsertEndChild(specular);

	TXML::XMLElement* ambient = document->NewElement("Ambient");
	ambient->SetAttribute("R", MBuffer->Get().Ambient.x);
	ambient->SetAttribute("G", MBuffer->Get().Ambient.y);
	ambient->SetAttribute("B", MBuffer->Get().Ambient.z);
	ambient->SetAttribute("A", MBuffer->Get().Ambient.w);
	property->InsertEndChild(ambient);

	TXML::XMLElement* emissive = document->NewElement("Emissive");
	emissive->SetAttribute("R", MBuffer->Get().Emissive.x);
	emissive->SetAttribute("G", MBuffer->Get().Emissive.y);
	emissive->SetAttribute("B", MBuffer->Get().Emissive.z);
	emissive->SetAttribute("A", MBuffer->Get().Emissive.w);
	property->InsertEndChild(emissive);

	property->SetAttribute("Shininess", MBuffer->Get().Shininess);
	property->SetAttribute("HasNormalMap", MBuffer->Get().HasNormalMap);
	material->InsertEndChild(property);

	document->SaveFile(File.c_str());
	delete document;
}

void Material::Load(string File)
{
	//this->File = File;

	TXML::XMLDocument* document = new TXML::XMLDocument();
	document->LoadFile(File.c_str());
	TXML::XMLElement* material = document->FirstChildElement();
	Name = material->Attribute("Name");

	TXML::XMLElement* shader = material->FirstChildElement();
	wstring shaderFile;
	shaderFile = ToString(shader->Attribute("Vertex"));
	shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
	VShader = ShaderManager::Get()->AddVS(shaderFile);
	shaderFile = ToString(shader->Attribute("Pixel");
	shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
	PShader = ShaderManager::Get()->AddPS(shaderFile);

	TXML::XMLElement* texture = shader->NextSiblingElement();
	wstring textureFile;
	textureFile = ToString(texture->Attribute("Diffuse"));
	SetDiffuseMap(textureFile);
	textureFile = ToString(texture->Attribute("Specular"));
	SetSpecularMap(textureFile);
	textureFile = ToString(texture->Attribute("Normal"));
	SetNormalMap(textureFile);

	TXML::XMLElement* property = texture->NextSiblingElement();
	TXML::XMLElement* diffuse = property->FirstChildElement();
	MBuffer->Get().Diffuse.x = diffuse->FloatAttribute("R");
	MBuffer->Get().Diffuse.y = diffuse->FloatAttribute("G");
	MBuffer->Get().Diffuse.z = diffuse->FloatAttribute("B");
	MBuffer->Get().Diffuse.w = diffuse->FloatAttribute("A");

	TXML::XMLElement* specular = property->NextSiblingElement();
	MBuffer->Get().Specular.x = specular->FloatAttribute("R");
	MBuffer->Get().Specular.y = specular->FloatAttribute("G");
	MBuffer->Get().Specular.z = specular->FloatAttribute("B");
	MBuffer->Get().Specular.w = specular->FloatAttribute("A");

	TXML::XMLElement* ambient = property->NextSiblingElement();
	MBuffer->Get().Ambient.x = ambient->FloatAttribute("R");
	MBuffer->Get().Ambient.y = ambient->FloatAttribute("G");
	MBuffer->Get().Ambient.z = ambient->FloatAttribute("B");
	MBuffer->Get().Ambient.w = ambient->FloatAttribute("A");

	TXML::XMLElement* emissive = property->NextSiblingElement();
	MBuffer->Get().Emissive.x = emissive->FloatAttribute("R");
	MBuffer->Get().Emissive.y = emissive->FloatAttribute("G");
	MBuffer->Get().Emissive.z = emissive->FloatAttribute("B");
	MBuffer->Get().Emissive.w = emissive->FloatAttribute("A");

	MBuffer->Get().Shininess = property->FloatAttribute("Shininess");
	MBuffer->Get().HasNormalMap = property->FloatAttribute("HasNormalMap");

	delete document;
}

void Material::GUIRender()
{
}

void Material::SaveDialog()
{
}

void Material::LoadDialog()
{
}
