#pragma once

#include "ModelData.h"

class ModelMesh;

class Model
{
public:
	Model(string Name);
	~Model();

	void PostUpdate();
	void Render();
	void GUIRender();

	void SetShader(wstring ShaderFile);

	void SetOwner(Transformation* Owner);

private:
	string Tag;

	Transformation Transform;
	
	vector<Material*> Materials;
	vector<ModelMesh*> Meshes;
	vector<BoneData> 
};

