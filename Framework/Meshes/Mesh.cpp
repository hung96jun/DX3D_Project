#include "Mesh.h"

Mesh::Mesh(const wstring ShaderFile)
	: Shape(ShaderFile)
{
}

Mesh::~Mesh()
{
}

void Mesh::ReadMesh(wstring File)
{
	File = L"../Datas/Models/" + File + L".mesh";
	BinaryRead* reader = new BinaryRead(ToString(File));
	
	UINT count = 0;
	count = reader->ReadUInt();

	for (UINT i = 0; i < count; i++)
	{
		
	}
}

void Mesh::ReadMaterial(wstring File)
{
}

void Mesh::ReadClip(wstring File)
{
}
