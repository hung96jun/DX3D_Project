#include "Matrix.h"

Matrix::Matrix()
{
	Value = XMMatrixIdentity();
}

Matrix::Matrix(Vector3 Pos, Vector3 Rot, Vector3 Scale)
{
	_11 = 0.0;
	_12 = 0.0;
	_13 = 0.0;
	_14 = 0.0;
	_21 = 0.0;
	_22 = 0.0;
	_23 = 0.0;
	_24 = 0.0;
	_31 = 0.0;
	_32 = 0.0;
	_33 = 0.0;
	_34 = 0.0;
	_41 = 0.0;
	_42 = 0.0;
	_43 = 0.0;
	_44 = 0.0;

}

Matrix::~Matrix()
{
}
