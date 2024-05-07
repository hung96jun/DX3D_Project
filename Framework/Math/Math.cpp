#include "Math.h"

const float Math::PI = 3.14159265f;

float Math::Radian(const float Degree)
{
	return Degree * PI / 180.0f;
}

float Math::Degree(const float Radian)
{
	return Radian * 180.0f / PI;
}

int Math::Random(const int Max, const int Min)
{
	return static_cast<int>(rand()) % (Max - Min + 1) + Min;
}

float Math::Random(const float Max, const float Min)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float diff = Max - Min;
	float value = random * diff;

	return value + Min;
}

Vector2 Math::RandomVector2(const float Max, const float Min)
{
	Vector2 value;
	value.X = Random(Max, Min);
	value.Y = Random(Max, Min);

	return value;
}

Vector3 Math::RandomVector3(const float Max, const float Min)
{
	Vector3 value;
	value.X = Random(Max, Min);
	value.Y = Random(Max, Min);
	value.Z = Random(Max, Min);

	return value;
}

float Math::VectorToRadian(Vector2 DirVector)
{
	DirVector.Normalize();
	float angle = static_cast<float>(atan2(static_cast<double>(DirVector.Y), 
		static_cast<double>(DirVector.X)));
	angle += XM_PI;

	return angle;
}

float Math::VectorToRadian(Vector3 DirVector)
{
	DirVector.Normalize();
	float angle = static_cast<float>(atan2(static_cast<double>(DirVector.Y), 
		static_cast<double>(DirVector.X)));
	angle += XM_PI;

	return angle;
}

float Math::VectorToDegree(Vector2 DirVector)
{
	return Degree(VectorToRadian(DirVector));
}

float Math::VectorToDegree(Vector3 DirVector)
{
	return Degree(VectorToRadian(DirVector));
}

float Math::Clamp(float Value, const float Min, const float Max)
{
	Value = Value > Max ? Max : Value;
	Value = Value < Min ? Min : Value;

	return Value;
}

void Math::Lerp(OUT Matrix& Out, const Matrix& M1, const Matrix& M2, float Amount)
{
	Float4x4 value, m1, m2;
	XMStoreFloat4x4(&value, Out);
	XMStoreFloat4x4(&m1, M1);
	XMStoreFloat4x4(&m2, M2);
	
	value._11 = m1._11 + (m2._11 - m1._11) * Amount;
	value._12 = m1._12 + (m2._12 - m1._12) * Amount;
	value._13 = m1._13 + (m2._13 - m1._13) * Amount;
	value._14 = m1._14 + (m2._14 - m1._14) * Amount;

	value._21 = m1._21 + (m2._21 - m1._21) * Amount;
	value._22 = m1._22 + (m2._22 - m1._22) * Amount;
	value._23 = m1._23 + (m2._23 - m1._23) * Amount;
	value._24 = m1._24 + (m2._24 - m1._24) * Amount;
	
	value._31 = m1._31 + (m2._31 - m1._31) * Amount;
	value._32 = m1._32 + (m2._32 - m1._32) * Amount;
	value._33 = m1._33 + (m2._33 - m1._33) * Amount;
	value._34 = m1._34 + (m2._34 - m1._34) * Amount;

	value._41 = m1._41 + (m2._41 - m1._41) * Amount;
	value._42 = m1._42 + (m2._42 - m1._42) * Amount;
	value._43 = m1._43 + (m2._43 - m1._43) * Amount;
	value._44 = m1._44 + (m2._44 - m1._44) * Amount;

	Out = XMMatrixSet(
		value._11, value._12, value._13, value._14, 
		value._21, value._22, value._23, value._24, 
		value._31, value._32, value._33, value._34,
		value._41, value._42, value._43, value._44
	);
}

Matrix Math::Lerp(const Matrix& Mat, const Matrix& M1, const Matrix& M2, float Amount)
{
	Float4x4 value, m1, m2;
	XMStoreFloat4x4(&value, Mat);
	XMStoreFloat4x4(&m1, M1);
	XMStoreFloat4x4(&m2, M2);

	value._11 = m1._11 + (m2._11 - m1._11) * Amount;
	value._12 = m1._12 + (m2._12 - m1._12) * Amount;
	value._13 = m1._13 + (m2._13 - m1._13) * Amount;
	value._14 = m1._14 + (m2._14 - m1._14) * Amount;

	value._21 = m1._21 + (m2._21 - m1._21) * Amount;
	value._22 = m1._22 + (m2._22 - m1._22) * Amount;
	value._23 = m1._23 + (m2._23 - m1._23) * Amount;
	value._24 = m1._24 + (m2._24 - m1._24) * Amount;

	value._31 = m1._31 + (m2._31 - m1._31) * Amount;
	value._32 = m1._32 + (m2._32 - m1._32) * Amount;
	value._33 = m1._33 + (m2._33 - m1._33) * Amount;
	value._34 = m1._34 + (m2._34 - m1._34) * Amount;

	value._41 = m1._41 + (m2._41 - m1._41) * Amount;
	value._42 = m1._42 + (m2._42 - m1._42) * Amount;
	value._43 = m1._43 + (m2._43 - m1._43) * Amount;
	value._44 = m1._44 + (m2._44 - m1._44) * Amount;

	return XMMatrixSet(
		value._11, value._12, value._13, value._14,
		value._21, value._22, value._23, value._24,
		value._31, value._32, value._33, value._34,
		value._41, value._42, value._43, value._44
	);
}

bool Math::NearlyEqual(const float& S1, const float& S2)
{
	return abs(S1 - S2) < FLT_EPSILON;
}
