#include "Libraries.h"
#include "Framework.h"

/**
* 브레이크 포인터 적중되지 않으면 해당 생성자 delete
*/
Projection::Projection()
	:Width(0.0f), Height(0.0f), Zn(0.0f), Zf(0.0f), Fov(0.0f)
{
	this->Mat = XMMatrixIdentity();
}

Projection::Projection(float Width, float Height, float Zn, float Zf, float Fov)
	:Width(Width), Height(Height), Zn(Zn), Zf(Zf), Fov(Fov)
{
}

Projection::~Projection()
{
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
