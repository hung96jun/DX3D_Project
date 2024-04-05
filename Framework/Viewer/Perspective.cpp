#include "Libraries.h"
#include "Perspective.h"

Perspective::Perspective(float Width, float Height, float Zn, float Zf, float Fov)
	:Projection(Width, Height, Zn, Zf, Fov)
{
	Set(Width, Height, Zn, Zf, Fov);
}

Perspective::~Perspective()
{
}

void Perspective::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	SUPER::Set(Width, Height, Zn, Zf, Fov);

	Aspect = Width / Height;
	this->Mat = XMMatrixPerspectiveFovLH(Fov, Aspect, Zn, Zf);
}
