#include "Framework.h"
#include "Viewport.h"

Viewport::Viewport(const float width, const float height, const float x, const float y, const float minDepth, const float maxDepth)
{
	Set(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
}

void Viewport::Set(const float width, const float height, const float x, const float y, const float minDepth, const float maxDepth)
{
	View.TopLeftX = this->X = x;
	View.TopLeftY = this->Y = y;
	View.Width = this->Width = width;
	View.Height = this->Height = height;
	View.MinDepth = this->MinDepth = minDepth;
	View.MaxDepth = this->MinDepth = maxDepth;

	RSSetViewport();
}

void Viewport::Projection(OUT Vector3* position, Vector3& source, Matrix& w, Matrix& v, Matrix& p)
{
	Matrix wvp = w * v * p;
	Vector3 temp = source;
	*position = XMVector3TransformCoord(temp.GetValue(), wvp);

	position->X = ((position->X + 1.0f) * 0.5f) * Width + X;
	position->Y = ((-position->Y + 1.0f) * 0.5f) * Height + Y;
	position->Z = (position->Z * (MaxDepth - MinDepth)) + MinDepth;
}

void Viewport::Unprojection(OUT Vector3* position, Vector3& source, Matrix& w, Matrix& v, Matrix& p)
{
	Vector3 temp = source;
	position->X = ((temp.X - X) / Width) * 2.0f - 1.0f;
	position->Y = (((temp.Y - Y) / Height) * 2.0f - 1.0f) * -1.0f;
	position->Z = (temp.Z - MinDepth) / (MaxDepth - MinDepth);

	Matrix wvp = w * v * p;
	wvp	= XMMatrixInverse(nullptr, wvp);
	*position = XMVector3TransformCoord(position->GetValue(), wvp);
}

void Viewport::RSSetViewport()
{
	D3D::GetDC()->RSSetViewports(1, &View);
}
