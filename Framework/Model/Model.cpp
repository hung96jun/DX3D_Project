#include "Libraries.h"
#include "Framework.h"
#include "Model.h"
#include "ModelMesh.h"

Model::Model(string Name)
{
}

Model::~Model()
{
	for (ModelBone* bone : Bones)
		SAFE_DELETE(bone);

	for (ModelMesh* mesh : Meshes)
		SAFE_DELETE(mesh);

	for (Material* mat : Materials)
		SAFE_DELETE(mat);

	//for (ModelClip* clip : Clips)
	//	SAFE_DELETE(clip);
}

void Model::ReadMesh(wstring File)
{
	File = L"../Datas/Models/" + File + L".mesh";

	BinaryRead* reader = new BinaryRead(File);

	UINT count = 0;
	count = reader->ReadUInt();
	for (UINT i = 0; i < count; i++)
	{
		ModelBone* bone = new ModelBone();
		bone->Index = reader->ReadInt();
		bone->Name = ToString(reader->ReadString());
		bone->ParentIndex = reader->ReadInt();
		bone->Transform = reader->ReadMatrix();

		Bones.push_back(bone);
	}

	count = reader->ReadUInt();
	for (UINT i = 0; i < count; i++)
	{
		ModelMesh* mesh = new ModelMesh();
		mesh->SetBoneIndex(reader->ReadInt());

		// Vertex Data
		{
			UINT count = reader->ReadUInt();

			vector<VertexModel> vertices;
			vertices.assign(count, VertexModel());

			reader->ReadByte((void**)&vertices, sizeof(VertexModel) * count);
			mesh->SetVertices(vertices);
			mesh->SetVertexCount(count);
		}

		// Index Data
		{
			UINT count = reader->ReadUInt();

			vector<UINT> indices;
			indices.assign(count, UINT());

			reader->ReadByte((void**)&indices, sizeof(UINT) * count);
			mesh->SetIndices(indices);
			mesh->SetIndexCount(count);
		}

		UINT partCount = reader->ReadUInt();
		for (UINT j = 0; j < partCount; j++)
		{
			ModelMeshPart* part = new ModelMeshPart();
			part->SetMaterial(ToString(reader->ReadString()));

			part->SetStartVertex(reader->ReadUInt());
			part->SetVertexCount(reader->ReadUInt());
			part->SetStartIndex(reader->ReadUInt());
			part->SetIndexCount(reader->ReadUInt());

			mesh->AddMeshPart(part);
		}

		Meshes.push_back(mesh);
	}// for(i)

	SAFE_DELETE(reader);

	BindBone();
}

void Model::ReadMaterial(wstring File)
{
	File = L"../Datas/Materials/" + File + L".material";

	TXML::XMLDocument* document = new TXML::XMLDocument();
	TXML::XMLError error = document->LoadFile(ToString(File).c_str());
	assert(error == TXML::XML_SUCCESS);

	TXML::XMLElement* root = document->FirstChildElement();
	TXML::XMLElement* materialNode = root->FirstChildElement();

	do
	{
		Material* material = new Material();

		TXML::XMLElement* node = nullptr;
		node = materialNode->FirstChildElement();
		material->SetTag(node->GetText());

		wstring directory = GetDirectory(File);
		directory.replace(directory.begin(), directory.end(), L"../Datas/Textures", L"");

		wstring texture = L"";
		node = node->NextSiblingElement();
		texture = ToString(node->GetText());

		if (texture.length() > 0)
			material->SetDiffuseMap(directory + texture);

		node = node->NextSiblingElement();
		texture = ToString(node->GetText());

		if (texture.length() > 0)
			material->SetSpecularMap(directory + texture);

		node = node->NextSiblingElement();
		texture = ToString(node->GetText());
		
		if (texture.length() > 0)
			material->SetNormalMap(directory + texture);

		Color color;
		node = node->NextSiblingElement();
		color.R = node->FloatAttribute("R");
		color.G = node->FloatAttribute("G");
		color.B = node->FloatAttribute("B");
		color.A = node->FloatAttribute("A");
		material->SetAmbient(color);

		node = node->NextSiblingElement();
		color.R = node->FloatAttribute("R");
		color.G = node->FloatAttribute("G");
		color.B = node->FloatAttribute("B");
		color.A = node->FloatAttribute("A");
		material->SetDiffuse(color);

		node = node->NextSiblingElement();
		color.R = node->FloatAttribute("R");
		color.G = node->FloatAttribute("G");
		color.B = node->FloatAttribute("B");
		color.A = node->FloatAttribute("A");
		material->SetSpecular(color);

		node = node->NextSiblingElement();
		color.R = node->FloatAttribute("R");
		color.G = node->FloatAttribute("G");
		color.B = node->FloatAttribute("B");
		color.A = node->FloatAttribute("A");
		material->SetEmissive(color);

		Materials.push_back(material);
		materialNode = materialNode->NextSiblingElement();
	} while (materialNode != nullptr);

	BineMesh();
}

void Model::ReadClip(wstring File)
{
}

void Model::BindBone()
{
	Root = Bones[0];
	for (ModelBone* bone : Bones)
	{
		if (bone->ParentIndex > -1)
		{
			bone->Parent = Bones[bone->ParentIndex];
			bone->Parent->Childs.push_back(bone);
		}
		else
			bone->Parent = nullptr;
	}
}

void Model::BineMesh()
{
	for (ModelMesh* mesh : Meshes)
	{
		mesh->SetBone(Bones[mesh->GetBoneIndex()]);
		/// 이 부분 확인해서 처리하기
		mesh->Binding();
	}
}
