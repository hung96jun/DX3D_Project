#include "Libraries.h"
#include "Framework.h"

#include "Utilities/Debug.h"

Projection::Projection(float Width, float Height, float Zn, float Zf, float Fov)
	:Width(Width), Height(Height), Zn(Zn), Zf(Zf), Fov(Fov)
{
	CONSTRUCTOR_DEBUG();

	this->Mat = XMMatrixIdentity();
	PBuffer = new MatrixBuffer();
}

Projection::~Projection()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(PBuffer);
}

void Projection::GetMatrix(Matrix* Mat)
{
	memcpy(Mat, &this->Mat, sizeof(Matrix));
}

void Projection::Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov)
{
	this->Width = Width;
	this->Height = Height;
	this->Zn = Zn;
	this->Zf = Zf;
	this->Fov = Fov;
}
