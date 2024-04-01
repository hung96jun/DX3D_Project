#pragma once
#include "Libraries.h"
#include "Math/Vector.h"

class Matrix
{
public:
	Matrix();
	Matrix(Vector3 Pos, Vector3 Rot, Vector3 Scale);
	~Matrix();

	///////////////////////////////////////////////////////////////////////////
	// Operator overloading
	///////////////////////////////////////////////////////////////////////////
	Matrix operator=(XMMATRIX& Mat)
	{
		Value = Mat;
		return *this;
	}

	XMMATRIX operator=(Matrix Mat)
	{
		Value = XMMatrixSet
		(
			_11, _12, _13, _14, 
			_21, _22, _23, _24, 
			_31, _32, _33, _34, 
			_41, _42, _43, _14
		);

		return Value;
	}
	///////////////////////////////////////////////////////////////////////////

	XMMATRIX Get() { return Value; }

	Vector3 Location() { return Vector3(_41, _42, _43); }
	Vector3 Scale() { return Vector3(_11, _22, _33); }

public:
	float _11 = 0.0;
	float _12 = 0.0;
	float _13 = 0.0;
	float _14 = 0.0;
	float _21 = 0.0;
	float _22 = 0.0;
	float _23 = 0.0;
	float _24 = 0.0;
	float _31 = 0.0;
	float _32 = 0.0;
	float _33 = 0.0;
	float _34 = 0.0;
	float _41 = 0.0;
	float _42 = 0.0;
	float _43 = 0.0;
	float _44 = 0.0;

private:
	XMMATRIX Value;

};

