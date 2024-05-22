#include "Libraries.h"
#include "Terrain.h"

Terrain::Terrain(const wstring ImageFile, const wstring ShaderFile)
	:Object(ShaderFile)
{


	Transform.Update();
}

Terrain::~Terrain()
{
}

void Terrain::Render()
{
}
