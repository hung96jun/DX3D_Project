#include "Libraries.h"
#include "Orthographic.h"
#include "Framework/Buffers/GlobalBuffer.h"

Orthographic::Orthographic(float Width, float Height, float Zn, float Zf, float Fov)
	:Projection(Width, Height, Zn, Zf, Fov)
{
	Set(Width, Height, Zn, Zf, Fov);
}

Orthographic::~Orthographic()
{
}

void Orthographic::Set()
{
	Set(Width, Height, Zn, Zf, Fov);
}

void Orthographic::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	SUPER::Set(Width, Height, Zn, Zf, Fov);

	this->Mat = XMMatrixOrthographicOffCenterLH(0.0f, Width, 0.0f, Height, Zn, Zf);

	PBuffer->Set(Mat);
	PBuffer->SetVS(2);
}
