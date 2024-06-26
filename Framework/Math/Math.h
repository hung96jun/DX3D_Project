#pragma once

#include "Vector.h"

struct Math
{
public:
	static const float PI;

	static float Radian(const float Degree);
	static float Degree(const float Radian);

	static int Random(const int Max, const int Min);
	static float Random(const float Max, const float Min);

	static Vector2 RandomVector2(const float Max, const float Min);
	static Vector3 RandomVector3(const float Max, const float Min);

	static float VectorToRadian(Vector2 DirVector);
	static float VectorToRadian(Vector3 DirVector);

	static float VectorToDegree(Vector2 DirVector);
	static float VectorToDegree(Vector3 DirVector);

	static float Clamp(float Value, const float Min, const float Max);

	static void Lerp(OUT Matrix& Out, const Matrix& M1, const Matrix& M2, float Amount);
	static Matrix Lerp(const Matrix& Mat, const Matrix& M1, const Matrix& M2, float Amount);

	static bool NearlyEqual(const float& S1, const float& S2);

	static Vector3 Cross(Vector3& Vec1, Vector3& Vec2);
	static float Dot(Vector3& Vec1, Vector3& Vec2);
};