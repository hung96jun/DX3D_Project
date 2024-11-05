#pragma once

#include "ModelData.h"

class ModelMesh;
class ModelBone;
class ModelMesh;
class ModelClip;
class Material;

class Model
{
public:
	Model(string Tag);
	~Model();

private:
	void BindBone();
	void BineMesh();

public:
	void Update();
	void Render();
	void GUIRender();

	//void SetShader(wstring File);
	void SetMeshShader(wstring File);
	void SetMaterialShader(wstring File);

	void ReadMesh(wstring File);
	void ReadMaterial(wstring File);
	void ReadClip(wstring File);

	const UINT BoneCount() { return static_cast<UINT>(Bones.size()); }
	vector<ModelBone*> GetBones() { return Bones; }
	ModelBone* BoneByIndex(const UINT Index) { return Bones[Index]; }
	ModelBone* BoneByName(const wstring Name);

	const UINT MeshCount() { return static_cast<UINT>(Meshes.size()); }
	vector<ModelMesh*>& GetMeshes() { return Meshes; }
	ModelMesh* MeshByIndex(const UINT Index) { return Meshes[Index]; }

	const UINT MaterialCount() { return static_cast<UINT>(Materials.size()); }
	vector<Material*>& GetMaterials() { return Materials; }
	Material* MaterialByIndex(const UINT Index) { return Materials[Index]; }
	Material* MaterialByName(const string Name);

	const UINT ClipCount() { return static_cast<UINT>(Clips.size()); }
	vector<ModelClip*>& GetClips() { return Clips; }
	ModelClip* ClipByIndex(UINT Index) { return Clips[Index]; }
	ModelClip* ClipByName(const wstring Tag);

private:
	string Tag;

	Transformation Transform;

	ModelBone* Root = nullptr;
	
	vector<ModelBone*> Bones;
	vector<ModelMesh*> Meshes;
	vector<Material*> Materials;
	vector<ModelClip*> Clips;

	//MatrixBuffer* WBuffer = nullptr;
};
