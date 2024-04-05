#include "Libraries.h"
#include "Orthographic.h"

Orthographic::Orthographic(float Width, float Height, float Zn, float Zf, float Fov)
	:Projection(Width, Height, Zn, Zf, Fov)
{
	Set(Width, Height, Zn, Zf, Fov);
}

Orthographic::~Orthographic()
{
}

void Orthographic::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	SUPER::Set(Width, Height, Zn, Zf, Fov);

	this->Mat = XMMatrixOrthographicLH(Width, Height, Zn, Zf);
}
