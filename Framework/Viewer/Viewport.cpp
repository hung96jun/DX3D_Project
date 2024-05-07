#include "Libraries.h"
#include "Framework.h"
#include "Utilities/Debug.h"

Viewport::Viewport(float Width, float Height, float X, float Y, float MinDepth, float MaxDepth)
{
	CONSTRUCTOR_DEBUG();

	Set(Width, Height, X, Y, MinDepth, MaxDepth);
}

Viewport::~Viewport()
{
	DESTRUCTOR_DEBUG();
}

void Viewport::RSSetViewport()
{
	D3D::GetDC()->RSSetViewports(1, &View);
}

void Viewport::Set(float Width, float Height, float X, float Y, float MinDepth, float MaxDepth)
{
	View.TopLeftX = this->X = X;
	View.TopLeftY = this->Y = Y;
	View.Width = this->Width = Width;
	View.Height = this->Height = Height;
	View.MinDepth = this->MinDepth = MinDepth;
	View.MaxDepth = this->MaxDepth = MaxDepth;

	RSSetViewport();
}
