#include "Libraries.h"
#include "Perspective.h"
#include "Framework/Buffers/GlobalBuffer.h"

#include "Utilities/Debug.h"

Perspective::Perspective(float Width, float Height, float Zn, float Zf, float Fov)
	:Projection(Width, Height, Zn, Zf, Fov)
{
	CONSTRUCTOR_DEBUG();

	Set(Width, Height, Zn, Zf, Fov);
}

Perspective::~Perspective()
{
	DESTRUCTOR_DEBUG();
}

void Perspective::Set()
{
	Set(Width, Height, Zn, Zf, Fov);
}

void Perspective::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	SUPER::Set(Width, Height, Zn, Zf, Fov);

	Aspect = Width / Height;
	this->Mat = XMMatrixPerspectiveFovLH(Fov, Aspect, Zn, Zf);
	//this->Mat = XMMatrixPerspectiveLH(XM_PIDIV4, (float)WIN_WIDTH / (float)WIN_HEIGHT, Zn, Zf);

	PBuffer->Set(Mat);
	PBuffer->SetVS(2);
}
