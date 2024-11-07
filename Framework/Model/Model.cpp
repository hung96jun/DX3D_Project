#include "Libraries.h"
#include "Framework.h"
#include "Model.h"
#include "ModelMesh.h"
#include "ModelClip.h"

Model::Model(string Tag)
	: Tag(Tag)
{
	CONSTRUCTOR_DEBUG();

	//WBuffer = new MatrixBuffer();
}

Model::~Model()
{
	DESTRUCTOR_DEBUG();

	for (ModelBone* bone : Bones)
		SAFE_DELETE(bone);

	for (ModelMesh* mesh : Meshes)
		SAFE_DELETE(mesh);

	for (Material* mat : Materials)
		SAFE_DELETE(mat);

	//for (ModelClip* clip : Clips)
	//	SAFE_DELETE(clip);

	//SAFE_DELETE(WBuffer);
}

void Model::Update()
{
	Transform.Update();
	for (ModelMesh* mesh : Meshes)
		mesh->Update();
}

void Model::Render()
{
	//WBuffer->Set(Transform.GetWorld());
	//WBuffer->SetVS(0);

	for (ModelMesh* mesh : Meshes)
		mesh->Render();

	//for (Material* mat : Materials)
	//	mat->Set();
}

void Model::Render(const UINT& DrawCount)
{
	for (ModelMesh* mesh : Meshes)
		mesh->Render(DrawCount);
}

void Model::GUIRender(const string Tag)
{
	if(ImGui::TreeNode(("Model" + Tag).c_str()))
	{
		for (int i = 0; i < Materials.size(); i++)
		{
			string temp = "";
			temp = "Material " + to_string(i);
			if (ImGui::TreeNode(temp.c_str()))
			{
				ImVec2 size = ImVec2(50, 50);
				ID3D11ShaderResourceView* texture = nullptr;
				texture = Materials[i]->GetDiffuseMap()->GetSRV();
				if (texture != nullptr)
					ImGui::Image(texture, size);
				texture = Materials[i]->GetSpecularMap()->GetSRV();
				if (texture != nullptr)
					ImGui::Image(texture, size);
				texture = Materials[i]->GetNormalMap()->GetSRV();
				if (texture != nullptr)
					ImGui::Image(texture, size);

				ImGui::TreePop();
			}
		}

		for (int i = 0; i < Meshes.size(); i++)
			Meshes[i]->GUIRender();

		ImGui::TreePop();
	}
}

void Model::SetMeshShader(wstring File)
{
	for (ModelMesh* mesh : Meshes)
		mesh->SetShader(File);
}

void Model::SetMaterialShader(wstring File)
{
	for (Material* mat : Materials)
		mat->SetShader(File);
}

void Model::ReadMesh(wstring File)
{
	File = L"../Datas/Models/" + File + L".txt";

	/**
	* reader 생성하는거 체크
	*/
	BinaryRead* reader = new BinaryRead(ToString(File));

	UINT count = 0;
	count = reader->ReadUInt();

	ModelBone* parentBone = nullptr;
	for (UINT i = 0; i < count; i++)
	{
		ModelBone* bone = new ModelBone();
		bone->Index = reader->ReadInt();
		bone->Name = ToString(reader->ReadString());
		bone->ParentIndex = reader->ReadInt();
		bone->Transform = reader->ReadMatrix();

		while (parentBone != nullptr)
		{
			if (bone->ParentIndex == parentBone->Index)
			{
				bone->Parent = parentBone;
				break;
			}

			else
				parentBone = parentBone->Parent;
		}

		Bones.push_back(bone);
		parentBone = bone;
	}

	count = reader->ReadUInt();
	for (UINT i = 0; i < count; i++)
	{
		ModelMesh* mesh = new ModelMesh();
		int index = reader->ReadInt();
		mesh->SetBoneIndex(index);

		// Vertex Data
		{
			UINT count = reader->ReadUInt();

			vector<VertexModel> vertices;
			vertices.assign(count, VertexModel());

			void* ptr = (void*)&(vertices[0]);
			reader->ReadByte(&ptr, sizeof(VertexModel) * count);
#if DEBUG == 1
			reader->DebugByte<VertexModel>(vertices);
#endif
			mesh->SetVertices(vertices);
			mesh->SetVertexCount(count);
		}

		// Index Data
		{
			UINT count = reader->ReadUInt();

			vector<UINT> indices;
			indices.assign(count, UINT());

			void* ptr = (void*)&(indices[0]);
			reader->ReadByte(&ptr, sizeof(UINT) * count);
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
		//directory = directory.replace(directory.begin(), directory.end(), L"../Datas/Materials/", L"");
		StringReplace(&directory, L"../Datas/", L"");

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
	//SetMaterialShader(L"ModelShader");

	for (Material* mat : Materials)
		mat->SetShader(L"ModelShader");
}

void Model::ReadClip(wstring File)
{
	File = L"../Datas/Clips/" + File + L".clip";

	BinaryRead* reader = new BinaryRead(ToString(File));

	ModelClip* clip = new ModelClip();
	clip->SetName(ToString(reader->ReadString()));
	clip->SetFrameRate(reader->ReadFloat());
	clip->SetFrameCount(reader->ReadDouble());	// 이부분 매개변수는 UINT이지만 호출된것은 double이므로 save할때 double인지 uint인지 재확인 필요

	UINT keyFrameCount = reader->ReadUInt();
	for (UINT i = 0; i < keyFrameCount; i++)
	{
		KeyFrame* frame = new KeyFrame();
		frame->BoneName = reader->ReadString();

		UINT size = reader->ReadUInt();
		if (size > 0)
		{
			frame->Positions.assign(size, KeyFrameData());
			reader->ReadByte((void**)&frame->Positions, sizeof(KeyFrameData) * size);
		}

		clip->SetKeyFrame(ToString(frame->BoneName), frame);
	}

	SAFE_DELETE(reader);
	Clips.push_back(clip);
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
		mesh->SetMaterials(Materials);
	}
}

ModelBone* Model::BoneByName(const wstring Name)
{
	for (ModelBone* bone : Bones)
	{
		if (bone->Name == Name)
			return bone;
	}

	return nullptr;
}

Material* Model::MaterialByName(const string Name)
{
	for (Material* material : Materials)
	{
		if (material->GetTag() == Name)
			return material;
	}

	return nullptr;
}

//ModelClip* Model::ClipByName(UINT Index)
//{
//	return nullptr;
//}
