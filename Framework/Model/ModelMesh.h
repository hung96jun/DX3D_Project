#pragma once

#include "Mesh.h"
#include "Renders/Material.h"
#include "Model/ModelData.h"

class ModelMesh
{
public:
	ModelMesh(string Name);
	~ModelMesh();

	void Render();
	void RenderInstance(UINT InstanceCount);

	void CreateMesh(void* VertexData, UINT VertexCount, void* IndexData, UINT IndexCount);

	void SetMaterial(Material* Mat) { this->Mat = Mat; }

private:
	string Name;

	Material* Mat;
	Mesh<ModelVertex>* MeshData;
};

