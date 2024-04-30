#pragma once

class ModelMesh
{
public:
	ModelMesh(string Name);
	~ModelMesh();

	void Render();
	void RenderInstance(UINT InstanceCount);

	void CreateMesh(void* VertexData, UINT VertexCount, void* IndexData, UINT IndexCount);

	//void SetMaterial(Material* Mat) { this->SetMaterial = Mat; }

private:

};

