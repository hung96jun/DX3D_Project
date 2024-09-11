#include "stdafx.h"
#include "ModelExporter.h"


ModelExporter::ModelExporter()
{
	CONSTRUCTOR_DEBUG();

	Importer = new Assimp::Importer();
}

ModelExporter::~ModelExporter()
{
	DESTRUCTOR_DEBUG();

	for (BoneData* bone : Bones)
		SAFE_DELETE(bone);

	for (MeshData* mesh : Meshes)
		SAFE_DELETE(mesh);

	for (Material* mat : Materials)
		SAFE_DELETE(mat);

	SAFE_DELETE(Importer);
}

void ModelExporter::ReadFile(wstring File)
{
	for (BoneData* bone : Bones)
		SAFE_DELETE(bone);

	for (MeshData* mesh : Meshes)
		SAFE_DELETE(mesh);

	for (Material* mat : Materials)
		SAFE_DELETE(mat);

	Bones.clear();
	Meshes.clear();
	Materials.clear();

	// 경로 확인해서 추가
	this->File = L"../Datas/Assets/Models/" + File;

	Scene = Importer->ReadFile
	(
		ToString(this->File),
		aiProcess_ConvertToLeftHanded
		| aiProcess_Triangulate
		| aiProcess_GenUVCoords
		| aiProcess_GenNormals
		| aiProcess_CalcTangentSpace
	);

	if (Scene == nullptr)
	{
		string str = Importer->GetErrorString();
		MessageBoxA(D3D::GetDesc().Handle, str.c_str(), "Assimp Error", MB_OK);
		exit(-1);
	}
}

void ModelExporter::ExportMesh(wstring SavePath)
{
	ReadBondData(Scene->mRootNode, -1, -1);
	ReadSkinData();

	// 경로 확인해서 수정
	//SavePath = L"../Datas/Models/" + SavePath + L".mesh";
	//WriteMeshData(ToString(SavePath));
	SavePath = L"../Datas/Models/" + SavePath + L".txt";
	WriteMeshData(ToString(SavePath));
}

void ModelExporter::ExportMaterial(wstring SavePath, bool bOverWrite)
{
	SavePath = L"../Datas/Materials/" + SavePath + L".material";
	if (bOverWrite == false)
	{
		if(ExistDirectory(ToString(SavePath)) == true)
			return;
	}

	ReadMaterialData();
	WriteMaterialData(ToString(SavePath));
}

void ModelExporter::GeClipList(vector<wstring>* Clips)
{
}

void ModelExporter::ExportAnimClip(UINT Index, wstring SavePath)
{
}

const bool ModelExporter::IsVailed()
{
	if (Scene == nullptr)
		return true;

	return false;
}

void ModelExporter::ReadBondData(aiNode* Node, int Index, int Parent)
{
	BoneData* bone = new BoneData();
	bone->Index = Index;
	bone->Parent = Parent;
	bone->Name = Node->mName.C_Str();

	Matrix transform(Node->mTransformation[0]);
	bone->Transform = XMMatrixTranspose(transform);

	Matrix parent;
	if (Parent <= 0)
		parent = XMMatrixIdentity();
	else
		parent = Bones[Parent]->Transform;

	bone->Transform = bone->Transform * parent;
	Bones.push_back(bone);

	ReadMeshData(Node, Index);

	// Recursion
	for (UINT i = 0; i < Node->mNumChildren; i++)
		ReadBondData(Node->mChildren[i], static_cast<int>(Bones.size()), Index);
}

void ModelExporter::ReadMeshData(aiNode* Node, int Index)
{
	if (Node->mNumMeshes < 1) return;

	MeshData* mesh = new MeshData();
	mesh->BoneIndex = Index;

	for (UINT i = 0; i < Node->mNumMeshes; i++)
	{
		UINT index = Node->mMeshes[i];
		aiMesh* src = Scene->mMeshes[index];

		UINT startVertex = static_cast<UINT>(mesh->Vertices.size());
		UINT startIndex = static_cast<UINT>(mesh->Indices.size());

		for (UINT j = 0; j < src->mNumVertices; j++)
		{
			VertexModel vertex;
			memcpy(&vertex.Position, &src->mVertices[j], sizeof(Float3));

			if (src->HasTextureCoords(0))
				memcpy(&vertex.Uv, &src->mTextureCoords[0][j], sizeof(Float2));
			if (src->HasNormals())
				memcpy(&vertex.Normal, &src->mNormals[j], sizeof(Float3));
			if (src->HasTangentsAndBitangents())
				memcpy(&vertex.Tangent, &src->mTangents[j], sizeof(Float3));

			mesh->Vertices.push_back(vertex);
		}

		for (UINT j = 0; j < src->mNumFaces; j++)
		{
			aiFace& face = src->mFaces[j];

			for (UINT k = 0; k < face.mNumIndices; k++)
				mesh->Indices.push_back(face.mIndices[k] + startVertex);
		}

		aiMaterial* mat = Scene->mMaterials[src->mMaterialIndex];
		MeshPart* part = new MeshPart();
		part->MaterialName = mat->GetName().C_Str();
		part->StartVertex = startVertex;
		part->StartIndex = startIndex;
		part->VertexCount = src->mNumVertices;
		part->IndexCount = src->mNumFaces * src->mFaces->mNumIndices;

		mesh->MeshParts.push_back(part);
	}// for - i

	Meshes.push_back(mesh);
}

void ModelExporter::ReadSkinData()
{
	for (UINT i = 0; i < Scene->mNumMeshes; i++)
	{
		aiMesh* meshInfo = Scene->mMeshes[i];
		if (meshInfo->HasBones() == false) continue;

		MeshData* mesh = Meshes[i];
		vector<BoneWeight> boneWeights;
		boneWeights.assign(mesh->Vertices.size(), BoneWeight());

		for (UINT i = 0; i < meshInfo->mNumBones; i++)
		{
			aiBone* boneInfo = meshInfo->mBones[i];

			UINT boneIndex = 0;
			for (BoneData* bone : Bones)
			{
				if (bone->Name == static_cast<string>(boneInfo->mName.C_Str()))
				{
					boneIndex = bone->Index;
					break;
				}
			}// for - bones

			for (UINT j = 0; j < boneInfo->mNumWeights; j++)
			{
				UINT index = boneInfo->mWeights[j].mVertexId;
				float weight = boneInfo->mWeights[j].mWeight;

				boneWeights[index].AddWeights(boneIndex, weight);
			}// for - j
		}// for - i

		for (UINT i = 0; i < boneWeights.size(); i++)
		{
			boneWeights[i].Normalize();

			BlendWeight blendWeight;
			boneWeights[i].GetBlendWeights(blendWeight);

			mesh->Vertices[i].Indices = blendWeight.Indices;
			mesh->Vertices[i].Weights = blendWeight.Weights;
		}
	}
}

void ModelExporter::WriteMeshData(string SavePath)
{
	if (SavePath.length() <= 0)
	{
		MessageBox(D3D::GetDesc().Handle, L"Warning", L"Model Exporter class - WriteMeshData function wrong path", MB_OK);
		return;
	}

	CreateFolders(SavePath);

	BinaryWrite* writer = new BinaryWrite(SavePath);
	writer->WriteUInt(static_cast<UINT>(Bones.size()));
	for (BoneData* bone : Bones)
	{
		writer->WriteInt(bone->Index);
		writer->WriteString(bone->Name);
		writer->WriteInt(bone->Parent);
		writer->WriteMatrix(bone->Transform);
	}

	writer->WriteUInt(static_cast<UINT>(Meshes.size()));
	for (MeshData* mesh : Meshes)
	{
		writer->WriteInt(mesh->BoneIndex);

		writer->WriteUInt(static_cast<UINT>(mesh->Vertices.size()));
		writer->WriteByte(mesh->Vertices.data(), sizeof(VertexModel) * static_cast<UINT>(mesh->Vertices.size()));
#if DEBUG == 1
		writer->DebugByte<VertexModel>(mesh->Vertices);
#endif

		//{
		//	void* debug = mesh->Vertices.data();
		//	vector<VertexModel>* test = static_cast<vector<VertexModel>*>(debug);
		//	string temp = "";
		//	for (int i = 0; i < test->size(); i++)
		//	{
		//		temp += ConvertToString<VertexModel>((*test)[i]);
		//	}
		//}
		
		writer->WriteUInt(static_cast<UINT>(mesh->Indices.size()));
		writer->WriteByte(mesh->Indices.data(), sizeof(UINT) * static_cast<UINT>(mesh->Indices.size()));
#if DEBUG == 1
		writer->DebugByte<UINT>(mesh->Indices);
#endif

		to_string(mesh->Indices[0]);

		writer->WriteUInt(static_cast<UINT>(mesh->MeshParts.size()));
		for (MeshPart* part : mesh->MeshParts)
		{
			writer->WriteString(part->MaterialName);

			writer->WriteUInt(part->StartVertex);
			writer->WriteUInt(part->VertexCount);

			writer->WriteUInt(part->StartIndex);
			writer->WriteUInt(part->IndexCount);
		}
	}

	SAFE_DELETE(writer);
}

void ModelExporter::ReadMaterialData()
{
	for (UINT i = 0; i < Scene->mNumMaterials; i++)
	{
		aiMaterial* src = Scene->mMaterials[i];
		if (FindMaterialData(src) == false)
			continue;

		Material* mat = new Material();
		mat->SetTag(src->GetName().C_Str());

		aiColor3D color;
		src->Get(AI_MATKEY_COLOR_AMBIENT, color);
		mat->SetAmbient(Color(color.r, color.g, color.b, 1.0f));
		
		src->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		mat->SetDiffuse(Color(color.r, color.g, color.b, 1.0f));

		float shininess;
		src->Get(AI_MATKEY_COLOR_SPECULAR, color);
		src->Get(AI_MATKEY_SHININESS, shininess);
		mat->SetSpecular(Color(color.r, color.g, color.b, shininess));
		
		src->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		mat->SetEmissive(Color(color.r, color.g, color.b, 1.0f));

		aiString file;
		src->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		mat->SetDiffuseFile(ToString(file.C_Str()));

		src->GetTexture(aiTextureType_SPECULAR, 0, &file);
		mat->SetSpecularFile(ToString(file.C_Str()));

		src->GetTexture(aiTextureType_NORMALS, 0, &file);
		mat->SetNormalFile(ToString(file.C_Str()));

		Materials.push_back(mat);
	}
}

bool ModelExporter::FindMaterialData(aiMaterial* Mat)
{
	string materialName = Mat->GetName().C_Str();

	bool bFound = false;
	for (MeshData* mesh : Meshes)
	{
		for (MeshPart* part : mesh->MeshParts)
		{
			if (part->MaterialName == materialName)
				return true;
		}
	}

	return false;
}

void ModelExporter::WriteMaterialData(string SavePath)
{
	string folder = GetDirectory(SavePath);
	string file = GetFileName(SavePath);
	CreateFolders(folder);

	// 파일이 있을경우 해당 파일의 내용 지우기
	ofstream ofs((folder + file), std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	tinyxml2::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	tinyxml2::XMLElement* root = document->NewElement("Materials");
	document->LinkEndChild(root);

	for (Material* mat : Materials)
	{
		tinyxml2::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);

		tinyxml2::XMLElement* element = nullptr;
		element = document->NewElement("Name");
		element->SetText(mat->GetTag().c_str());
		node->LinkEndChild(element);

		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, ToString(mat->GetDiffuseFile())).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, ToString(mat->GetSpecularFile())).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, ToString(mat->GetNormalFile())).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("Ambient");
		element->SetAttribute("R", mat->GetAmbient().X);
		element->SetAttribute("G", mat->GetAmbient().Y);
		element->SetAttribute("B", mat->GetAmbient().Z);
		element->SetAttribute("A", mat->GetAmbient().W);
		node->LinkEndChild(element);

		element = document->NewElement("Diffuse");
		element->SetAttribute("R", mat->GetDiffuse().X);
		element->SetAttribute("G", mat->GetDiffuse().Y);
		element->SetAttribute("B", mat->GetDiffuse().Z);
		element->SetAttribute("A", mat->GetDiffuse().W);
		node->LinkEndChild(element);

		element = document->NewElement("Specular");
		element->SetAttribute("R", mat->GetSpecular().X);
		element->SetAttribute("G", mat->GetSpecular().Y);
		element->SetAttribute("B", mat->GetSpecular().Z);
		element->SetAttribute("A", mat->GetSpecular().W);
		node->LinkEndChild(element);

		element = document->NewElement("Emissive");
		element->SetAttribute("R", mat->GetEmissive().X);
		element->SetAttribute("G", mat->GetEmissive().Y);
		element->SetAttribute("B", mat->GetEmissive().Z);
		element->SetAttribute("A", mat->GetEmissive().W);
		node->LinkEndChild(element);
	}

	document->SaveFile((folder + file).c_str());
	SAFE_DELETE(document);
}

string ModelExporter::WriteTexture(string SaveFolder, string File)
{
	if (File.length() < 1) return "";

	string fileName = GetFileName(File);
	const aiTexture* texture = Scene->GetEmbeddedTexture(File.c_str());

	string path = "";
	if (texture != nullptr)
	{
		path = SaveFolder + GetFileNameWithoutExtension(File) + ".png";
		BinaryWrite* writer = new BinaryWrite(path);
		writer->WriteByte(texture->pcData, texture->mWidth);
		SAFE_DELETE(writer);
	}
	else
	{
		string directory = ToString(GetDirectory(this->File));
		string origin = directory + File;
		if (origin.find("\\") != string::npos)
			origin.replace(origin.begin(), origin.end(), "\\", "/");

		if (ExistDirectory(SaveFolder) == true)
			return "";

		path = SaveFolder + fileName;
		CopyFileA(origin.c_str(), path.c_str(), FALSE);

		path.replace(path.begin(), path.end(), L"../Datas/Materials/", L"");
	}

	return GetFileName(path);
}

//ClipData* ModelExporter::ReadClipData(aiAnimation* Anim)
//{
//	return nullptr;
//}
//
//void ModelExporter::ReadKeyFrameData(ClipData* Clip, aiNode* Node, vector<ClipNode> AnimNodeInfos)
//{
//}
//
//void ModelExporter::WriteClipDat(ClipData* Clip, wstring SavePath)
//{
//}




