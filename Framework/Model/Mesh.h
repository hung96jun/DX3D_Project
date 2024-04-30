#pragma once

#include "Libraries.h"
#include "Framework/Buffers/VertexBuffer.h"
#include "Framework/Buffers/IndexBuffer.h"
#include "Systems/D3D.h"

template<typename T>
class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	void Draw(D3D11_PRIMITIVE_TOPOLOGY Type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void DrawInstance(UINT InstanceCount, D3D11_PRIMITIVE_TOPOLOGY Type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	void CreatMesh();
	void UpdateVertex();
	void UpdateIndex();

	vector<T>& GetVertices() { return Vertices; }
	vector<UINT>& GetIndices() { return Indices; }

private:
	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;

	vector<T> Vertices;
	vector<UINT> Indices;
};

template<typename T>
inline Mesh<T>::~Mesh()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
}

template<typename T>
inline void Mesh<T>::Draw(D3D11_PRIMITIVE_TOPOLOGY Type)
{
	VBuffer->Set(Type);

	if (IBuffer)
	{
		IBuffer->Set();
		D3D::GetDC()->DrawIndexed(Indices.size(), 0, 0);
	}
	else
		D3D::GetDC()->Draw(Vertices.size(), 0);
}

template<typename T>
inline void Mesh<T>::DrawInstance(UINT InstanceCount, D3D11_PRIMITIVE_TOPOLOGY Type)
{
	VBuffer->Set(Type);
	
	if (IBuffer)
	{
		IBuffer->Set();
		D3D::GetDC()->DrawIndexedInstanced(Indices.size(), InstanceCount, 0, 0, 0);
	}
	else
		D3D::GetDC()->DrawInstanced(Vertices.size(), InstanceCount, 0, 0);
}

template<typename T>
inline void Mesh<T>::CreatMesh()
{
	if (Vertices.size() > 0)
		VBuffer = new VertexBuffer(Vertices.data(), sizeof(T), Vertices.size());

	if (Indices.size() > 0)
		IBuffer = new IndexBuffer(Indices.data(), Indices.size());
}

template<typename T>
inline void Mesh<T>::UpdateVertex()
{
	VBuffer->Update(Vertices.data(), Vertices.size());
}

template<typename T>
inline void Mesh<T>::UpdateIndex()
{
	IBuffer->Update(Indices.data(), Indices.size());
}
