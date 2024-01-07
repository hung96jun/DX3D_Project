#pragma once

class Viewport
{
public:
	Viewport(const float width, const float height, const float x = 0, const float y = 0, const float minDepth = 0, const float maxDepth = 1);
	~Viewport();

	void RSSetViewport();
	void Set(const float width, const float height, const float x = 0, const float y = 0, const float minDepth = 0, const float maxDepth = 1);

	const float GetWidth() const { return Width; }
	const float GetHeight() const { return Height; }

	//void GetRay(OUT Vector3* position, OUT Vector3* direction, Matrix& w, Matrix& v, Matrix& p);

	void Projection(OUT Vector3* position, Vector3& source, Matrix& w, Matrix& v, Matrix& p);
	void Unprojection(OUT Vector3* position, Vector3& source, Matrix& w, Matrix& v, Matrix& p);

private:
	float X, Y;
	float Width, Height;
	float MinDepth, MaxDepth;

	D3D11_VIEWPORT View;
};