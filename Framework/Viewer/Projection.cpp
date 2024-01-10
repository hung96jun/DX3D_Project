#include "Libraries.h"
//#include "Framework.h"
#include "Projection.h"

Projection::Projection() 
	: Width(0.0f), Height(0.0f), ZF(0.0f), ZN(0.0f), Fov(0.0f)
{
	ProjMatrix = XMMatrixIdentity();
}

Projection::Projection(const float width, const float height, const float zn, const float zf, const float fov)
	: Width(width), Height(height), ZN(zn), ZF(zf), Fov(fov)
{
}

Projection::~Projection()
{
}

void Projection::GetMatrix(Matrix* matrix)
{
	memcpy(matrix, &Perspective, sizeof(Matrix));
}

void Projection::Set(const float width, const float height, const float zn, const float zf, const float fov)
{
	Width = width;
	Height = height;
	ZN = zn;
	ZF = zf;
	Fov = fov;
}
