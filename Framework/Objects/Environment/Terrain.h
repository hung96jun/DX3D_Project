#pragma once

#include "Objects/Object.h"

class Terrain : public Object
{
public:
	Terrain(const wstring ImageFile, const wstring ShaderFile = L"SimpleShader");
	virtual ~Terrain();

	//virtual void Update();
	virtual void Render();

private:
	UINT Width, Height;
};