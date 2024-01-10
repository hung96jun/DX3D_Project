#include "Libraries.h"
#include "Orthgraphic.h"

Orthgraphic::Orthgraphic(const float width, const float height, const float zn, const float zf)
	: Projection(width, height, zn, zf, 0.0f)
{
	Set(width, height, zn, zf, 0.0f);
}

Orthgraphic::~Orthgraphic()
{
}

void Orthgraphic::Set(const float width, const float height, const float zn, const float zf, const float fov)
{
	SUPER::Set(width, height, zn, zf, fov);

	ProjMatrix = XMMatrixOrthographicLH(width, height, zn, zf);
}
