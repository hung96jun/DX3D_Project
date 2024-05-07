#pragma once
#include "Libraries.h"

struct Vector2
{
public:
	Vector2() : X(0.0f), Y(0.0f) {}
	//Vector2(double n) : X(static_cast<float>(n)), Y(static_cast<float>(n)) {}
	//Vector2(double x, double y) : X(static_cast<float>(x)), Y(static_cast<float>(y)) {}
	Vector2(float n) : X(n), Y(n) {}
	Vector2(float x, float y) : X(x), Y(y) {}
	Vector2(XMVECTOR value)
	{
		X = XMVectorGetX(value);
		Y = XMVectorGetY(value);
	}

	//////////////////////////////////////////////////////////////////////////////
	// operator overloading
	//////////////////////////////////////////////////////////////////////////////
	const bool operator==(const Vector2& value) const { return (X == value.X) && (Y == value.Y); }
	const bool operator!=(const Vector2& value) const { return (X != value.X) || (Y != value.Y); }
	
	Vector2 operator+(const float& value) const { return Vector2(X + value, Y + value); }
	Vector2 operator-(const float& value) const { return Vector2(X - value, Y - value); }
	Vector2 operator*(const float& value) const { return Vector2(X * value, Y * value); }
	Vector2 operator/(const float& value) const { return Vector2(X / value, Y / value); }
	Vector2 operator+(const Vector2& value) const { return Vector2(X + value.X, Y + value.Y); }
	Vector2 operator-(const Vector2& value) const { return Vector2(X - value.X, Y - value.Y); }

	const Vector2 operator-() const { return Vector2(-X, -Y); }
	
	//Float2 operator=(const Vector2& Value)
	//{
	//	return Float2(Value.X, Value.Y);
	//}

	Vector2& operator+=(const float& value)
	{
		X += value;
		Y += value;

		return *this;
	}
	Vector2& operator-=(const float& value)
	{
		X -= value;
		Y -= value;

		return *this;
	}
	Vector2& operator*=(const float& value)
	{
		X *= value;
		Y *= value;

		return *this;
	}
	Vector2& operator/=(const float& value)
	{
		X /= value;
		Y /= value;

		return *this;
	}
	Vector2& operator+=(const Vector2& value)
	{
		X += value.X;
		Y += value.Y;

		return *this;
	}
	Vector2& operator-=(const Vector2& value)
	{
		X -= value.X;
		Y -= value.Y;

		return *this;
	}
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	// functions
	//////////////////////////////////////////////////////////////////////////////
	const float Length() const { return sqrt(X * X + Y * Y); }
	const float Angle() const { return atan2(Y, X); }
	static const Vector2 ZeroVector() { return Vector2(0.0f, 0.0f); }

	Vector2 GetNormalize() const
	{
		float length = Length();
		return Vector2(X / length, Y / length);
	}

	void Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
	}

	string ToString() const
	{
		return ("X : " + to_string(X) + ", Y : " + to_string(Y));
	}
	//////////////////////////////////////////////////////////////////////////////

	XMVECTOR GetValue() { return XMVectorSet(X, Y, 0.0f, 0.0f); }

public:
	float X = 0.0;
	float Y = 0.0;
};

struct Vector3
{
public:
	Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
	Vector3(float n) : X(n), Y(n), Z(n) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(XMVECTOR value)
	{
		X = XMVectorGetX(value);
		Y = XMVectorGetY(value);
		Z = XMVectorGetZ(value);
	}

	//////////////////////////////////////////////////////////////////////////////
	// operator overloading
	//////////////////////////////////////////////////////////////////////////////
	const bool operator==(const Vector3& value)
	{
		return (X == value.X && Y == value.Y && Z == value.Z);
	}
	const bool operator!=(const Vector3& value)
	{
		return (X != value.X || Y != value.Y || Z != value.Z);
	}

	Vector3& operator=(const Float3& value)
	{
		X = value.x;
		Y = value.y;
		Z = value.z;

		return *this;
	}

	const Vector3 operator+(const float& value) const { return Vector3(X + value, Y + value, Z + value); }
	const Vector3 operator-(const float& value) const { return Vector3(X - value, Y - value, Z - value); }
	const Vector3 operator+(const Vector3& value) const { return Vector3(X + value.X, Y + value.Y, Z + value.Z); }
	const Vector3 operator-(const Vector3& value) const { return Vector3(X - value.X, Y - value.Y, Z - value.Z); }
	const Vector3 operator*(const float& value) const { return Vector3(X * value, Y * value, Z * value); }
	const Vector3 operator/(const float& value) const { return Vector3(X / value, Y / value, Z / value); }

	const Vector3 operator-() const { return Vector3(-X, -Y, -Z); }

	//Float3 operator=(const Vector3& Value)
	//{
	//	return Float3(Value.X, Value.Y, Value.Z);
	//}

	operator Float3() const 
	{
		return Float3(X, Y, Z);
	}

	Vector3& operator+=(const float& value)
	{
		X += value;
		Y += value;
		Z += value;

		return *this;
	}
	Vector3& operator-=(const float& value)
	{
		X -= value;
		Y -= value;
		Z -= value;

		return *this;
	}
	Vector3& operator+=(const Vector3& value)
	{
		X += value.X;
		Y += value.Y;
		Z += value.Z;

		return *this;
	}
	Vector3& operator-=(const Vector3& value)
	{
		X -= value.X;
		Y -= value.Y;
		Z -= value.Z;

		return *this;
	}
	Vector3& operator*=(const float& value)
	{
		X *= value;
		Y *= value;
		Z *= value;

		return *this;
	}
	Vector3& operator/=(const float& value)
	{
		X /= value;
		Y /= value;
		Z /= value;

		return *this;
	}

	Vector3& operator=(const XMVECTOR& value)
	{
		X = XMVectorGetX(value);
		Y = XMVectorGetY(value);
		Z = XMVectorGetZ(value);

		return *this;
	}
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	// functions
	//////////////////////////////////////////////////////////////////////////////
	const float Length() const { return sqrt(X * X + Y * Y + Z * Z); }

	Vector3 GetNormalize() const
	{
		float length = Length();
		return Vector3(X / length, Y / length, Z / length);
	}

	void Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
		Z /= length;
	}

	static const Vector3 ZeroVector() { return Vector3(0.0, 0.0, 0.0); }
	static const Vector3 Right() { return Vector3(1.0, 0.0, 0.0); }
	static const Vector3 Up() { return Vector3(0.0, 1.0, 0.0); }
	static const Vector3 Forward() { return Vector3(0.0, 0.0, 1.0); }

	string ToString() const
	{
		return ("X : " + to_string(X) + ", Y : " + to_string(Y) + ", Z : " + to_string(Z));
	}

	XMVECTOR GetValue() const { return XMVectorSet(X, Y, Z, 0.0f); }
	//////////////////////////////////////////////////////////////////////////////

public:
	float X = 0.0;
	float Y = 0.0;
	float Z = 0.0;
};


struct Vector4
{
public:
	Vector4() {}
	Vector4(float n) : X(n), Y(n), Z(n), W(n) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	Vector4(XMVECTOR value)
	{
		X = XMVectorGetX(value);
		Y = XMVectorGetY(value);
		Z = XMVectorGetZ(value);
		W = XMVectorGetW(value);
	}



	//////////////////////////////////////////////////////////////////////////////
	// functions
	//////////////////////////////////////////////////////////////////////////////
	static const Vector4 ZeroVector() { return Vector4(0.0, 0.0, 0.0, 0.0); }
	static const Vector4 Right() { return Vector4(1.0, 0.0, 0.0, 0.0); }
	static const Vector4 Up() { return Vector4(0.0, 1.0, 0.0, 0.0); }
	static const Vector4 Forward() { return Vector4(0.0, 0.0, 1.0, 0.0); }

	string ToString() const
	{
		return ("X : " + to_string(X) + ", Y : " + to_string(Y) + ", Z : " + to_string(Z) + ", W : " + to_string(W));
	}

	XMVECTOR GetValue() { return XMVectorSet(X, Y, Z, W); }
	//////////////////////////////////////////////////////////////////////////////

public:
	float X = 0.0;
	float Y = 0.0;
	float Z = 0.0;
	float W = 0.0;
};