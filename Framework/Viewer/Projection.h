#pragma once

class Projection
{
public:
	Projection(const float width, const float height, const float zn, const float zf, const float fov);
	virtual ~Projection();

	void GetMatrix(Matrix* matrix);

protected:
	Projection();
	virtual void Set(const float width, const float height, const float zn, const float zf, const float fov);
	
protected:
	float Width, Height;
	float ZN, ZF;
	float Fov;

	Matrix ProjMatrix;
};