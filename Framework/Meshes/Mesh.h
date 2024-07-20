#pragma once

#include "Shape.h"

class Mesh : public Shape
{
public:
	Mesh(const wstring ShaderFile = L"TestTextureShader");
	~Mesh();

public:
	void ReadMesh(wstring File);
	void ReadMaterial(wstring File);
	void ReadClip(wstring File);
};

