#include "Libraries.h"
#include "Orthographic.h"
#include "Framework/Buffers/GlobalBuffer.h"

#include "Utilities/Debug.h"

Orthographic::Orthographic(float Width, float Height, float Zn, float Zf, float Fov)
	:Projection(Width, Height, Zn, Zf, Fov)
{
	CONSTRUCTOR_DEBUG();

	Set(Width, Height, Zn, Zf, Fov);
}

Orthographic::~Orthographic()
{
	DESTRUCTOR_DEBUG();
}

void Orthographic::Set()
{
	Set(Width, Height, Zn, Zf, Fov);
}

void Orthographic::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	SUPER::Set(Width, Height, Zn, Zf, Fov);

	XMMatrixOrthographicOffCenterLH(0.0, Width, 0.0, Height, -1.0f, 1.0f);

	//PBuffer->Set(Mat);
	//PBuffer->SetVS(2);
}
