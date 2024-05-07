#pragma once

#include "Renders/Material.h"
#include "Model/ModelData.h"

class ModelExporter
{
public:
	ModelExporter() = delete;
	ModelExporter(const string Name, const string File);
	~ModelExporter();

	void ExportMaterial();
	void ExportMesh();
	void ExportClip(const string ClipName);

private:
	///////////////////////////////////////////////////////////////////////////
	// Material
	///////////////////////////////////////////////////////////////////////////
	void ReadMaterial();
	void WriteMaterial();
	const string CreateTexture(string File);
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Mesh
	///////////////////////////////////////////////////////////////////////////
	void ReadMesh(aiNode* Node);
	void ReadNode(aiNode* Node, const int Index, const int Parent);
	void ReadBone(aiMesh* Mesh, vector<VertexWeights>& VertexWeights);
	void WriteMesh();
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Clip
	///////////////////////////////////////////////////////////////////////////
	Clip* ReadClip(aiAnimation* Animation);
	void ReadKeyFrame(Clip* AnimClip, aiNode* Node, vector<ClipNode>& ClipNodes);
	void WriterClip(Clip* AnimClip, const string ClipName, const UINT Index);
	///////////////////////////////////////////////////////////////////////////

private:
	Assimp::Importer* Importer;
	const aiScene* Scene;

	string Name;

	vector<Material*> Materials;
	vector<MeshData*> Meshes;
	vector<NodeData*> Nodes;
	vector<BoneData*> Bones;

	map<string, UINT> BoneMap;
	UINT BoneCount = 0;
};

