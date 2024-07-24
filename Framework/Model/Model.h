#pragma once

#include "ModelData.h"

class ModelMesh;
class ModelBone;
class ModelMesh;
class Material;

class Model
{
public:
	Model(string Name);
	~Model();

private:
	void ReadMesh(wstring File);
	void ReadMaterial(wstring File);
	void ReadClip(wstring File);
	
	void BindBone();
	void BineMesh();

private:
	string Tag;

	Transformation Transform;

	ModelBone* Root = nullptr;
	
	vector<ModelBone*> Bones;
	vector<ModelMesh*> Meshes;
	vector<Material*> Materials;
	//vector<ModelClip*> Clips;
};

