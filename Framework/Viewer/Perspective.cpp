#include "Libraries.h"
#include "Perspective.h"

Perspective::Perspective(const float width, const float height, const float zn, const float zf, const float fov)
	: Projection(width, height, zn, zf, fov)
{
	Set(width, height, zn, zf, fov);
}

Perspective::~Perspective()
{
}

void Perspective::Set(const float width, const float height, const float zn, const float zf, const float fov)
{
	SUPER::Set(width, height, zn, zf, fov);

	Aspect = width / height;
	ProjMatrix = XMMatrixPerspectiveFovLH(fov, Aspect, zn, zf);
}
