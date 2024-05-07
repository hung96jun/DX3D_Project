#include "Libraries.h"
#include "ModelMesh.h"
#include "Framework/Buffers/GlobalBuffer.h"

ModelMesh::ModelMesh(string Name)
{
	CONSTRUCTOR_DEBUG();
}

ModelMesh::~ModelMesh()
{
	DESTRUCTOR_DEBUG();

	delete MeshData;
}

void ModelMesh::Render()
{
	Mat->Set();
	MeshData->Draw();
}

void ModelMesh::RenderInstance(UINT InstanceCount)
{
	Mat->Set();
	MeshData->DrawInstance(InstanceCount);
}

void ModelMesh::CreateMesh(void* VertexData, UINT VertexCount, void* IndexData, UINT IndexCount)
{
	MeshData = new Mesh<ModelVertex>();

	MeshData->GetVertices().resize(VertexCount);
	memcpy(MeshData->GetVertices().data(), VertexData, sizeof(ModelVertex) * VertexCount);

	MeshData->GetIndices().resize(IndexCount);
	memcpy(MeshData->GetIndices().data(), IndexData, sizeof(UINT) * IndexCount);

	MeshData->CreatMesh();
}
