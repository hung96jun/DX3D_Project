#pragma once

#include "Model/ModelData.h"

class ModelExporter
{
public:
	ModelExporter();
	~ModelExporter();

	void ReadFile(wstring File);

	void ExportMesh(wstring SavePath);
	void ExportMaterial(wstring SavePath, bool bOverWrite = true);

	void GeClipList(vector<wstring>* Clips);
	void ExportAnimClip(UINT Index, wstring SavePath);

	/**
	* 무효 체크
	* @return	true	무효
	* @return	false	유효
	*/
	const bool IsVailed();

private:
	void ReadBondData(aiNode* Node, int Index, int Parent);
	void ReadMeshData(aiNode* Node, int Index);
	void ReadSkinData();
	void WriteMeshData(string SavePath);

	void ReadMaterialData();
	bool FindMaterialData(aiMaterial* Mat);
	void WriteMaterialData(string SavePath);
	string WriteTexture(string SaveFolder, string File);

	//ClipData* ReadClipData(aiAnimation* Anim);
	//void ReadKeyFrameData(ClipData* Clip, aiNode* Node, vector<ClipNode> AnimNodeInfos);
	//void WriteClipDat(ClipData* Clip, wstring SavePath);

private:
	wstring File;

	Assimp::Importer* Importer;
	const aiScene* Scene;

	vector<Material*> Materials;
	vector<MeshData*> Meshes;
	//vector<NodeData*> Nodes;
	vector<BoneData*> Bones;

	map<string, UINT> BoneMap;
	UINT BoneCount = 0;
};

