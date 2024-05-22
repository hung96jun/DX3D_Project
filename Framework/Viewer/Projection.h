#pragma once

class MatrixBuffer;

class Projection
{
protected:
	Projection() = delete;

public:
	Projection(float Width, float Height, float Zn, float Zf, float Fov);
	virtual ~Projection();

	void GetMatrix(Matrix* Mat);
	Matrix& GetMatrix() { return Mat; }
	
protected:
	virtual void Set(const float Width, const float Height, const float Zn, const float Zf, const float Fov);
	
protected:
	float Width, Height;
	float Zn, Zf;
	float Fov;

	Matrix Mat;
	//MatrixBuffer* PBuffer;
};

