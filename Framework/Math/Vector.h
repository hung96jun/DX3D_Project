#pragma once
#include "Libraries.h"

struct Vector2
{
public:
	Vector2() {}
	Vector2(double n) : X(n), Y(n) {}
	Vector2(double x, double y) : X(x), Y(y) {}
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
	const bool operator==(const Vector2& value) const
	{
		return (X == value.X) && (Y == value.Y);
	}
	const bool operator!=(const Vector2& value) const
	{
		return (X != value.X) || (Y != value.Y);
	}

	Vector2 operator+(const double& value) const
	{
		return Vector2(X + value, Y + value);
	}
	Vector2 operator-(const double& value) const
	{
		return Vector2(X - value, Y - value);
	}
	Vector2 operator*(const double& value) const
	{
		return Vector2(X * value, Y * value);
	}
	Vector2 operator/(const double& value) const
	{
		return Vector2(X / value, Y / value);
	}
	Vector2 operator+(const Vector2& value) const
	{
		return Vector2(X + value.X, Y + value.Y);
	}
	Vector2 operator-(const Vector2& value) const
	{
		return Vector2(X - value.X, Y - value.Y);
	}

	Vector2& operator+=(const double& value)
	{
		X += value;
		Y += value;

		return *this;
	}
	Vector2& operator-=(const double& value)
	{
		X -= value;
		Y -= value;

		return *this;
	}
	Vector2& operator*=(const double& value)
	{
		X *= value;
		Y *= value;

		return *this;
	}
	Vector2& operator/=(const double& value)
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
	const double Length() const { return sqrt(X * X + Y * Y); }
	const double Angle() const { return atan2(Y, X); }
	static const Vector2 ZeroVector() { return Vector2(0.0f, 0.0f); }

	Vector2 GetNormalize() const
	{
		double length = Length();
		return Vector2(X / length, Y / length);
	}

	void Normalize()
	{
		double length = Length();
		X /= length;
		Y /= length;
	}

	string ToString()
	{
		return ("X : " + to_string(X) + ", Y : " + to_string(Y));
	}
	//////////////////////////////////////////////////////////////////////////////

	XMVECTOR GetValue() { return XMVectorSet(static_cast<float>(X), static_cast<float>(Y), 0.0f, 0.0f); }

public:
	double X = 0.0;
	double Y = 0.0;
};

struct Vector3
{
public:
	Vector3() {}
	Vector3(double n) : X(n), Y(n), Z(n) {}
	Vector3(double x, double y, double z) : X(x), Y(y), Z(z) {}
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

	const Vector3 operator+(const double& value) const { return Vector3(X + value, Y + value, Z + value); }
	const Vector3 operator-(const double& value) const { return Vector3(X - value, Y - value, Z - value); }
	const Vector3 operator+(const Vector3& value) const { return Vector3(X + value.X, Y + value.Y, Z + value.Z); }
	const Vector3 operator-(const Vector3& value) const { return Vector3(X - value.X, Y - value.Y, Z - value.Z); }
	const Vector3 operator*(const double& value) const { return Vector3(X * value, Y * value, Z * value); }
	const Vector3 operator/(const double& value) const { return Vector3(X / value, Y / value, Z / value); }

	Vector3& operator+=(const double& value)
	{
		X += value;
		Y += value;
		Z += value;

		return *this;
	}
	Vector3& operator-=(const double& value)
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
	Vector3& operator*=(const double& value)
	{
		X *= value;
		Y *= value;
		Z *= value;

		return *this;
	}
	Vector3& operator/=(const double& value)
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
	const double Length() const { return sqrt(X * X + Y * Y + Z * Z); }

	Vector3 GetNormalize() const
	{
		double length = Length();
		return Vector3(X / length, Y / length, Z / length);
	}

	void Normalize()
	{
		double length = Length();
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

	XMVECTOR GetValue() { return XMVectorSet(static_cast<float>(X), static_cast<float>(Y), static_cast<float>(Z), 0.0f); }
	//////////////////////////////////////////////////////////////////////////////

public:
	double X = 0.0;
	double Y = 0.0;
	double Z = 0.0;
};


struct Vector4
{
public:
	Vector4() {}
	Vector4(double n) : X(n), Y(n), Z(n), W(n) {}
	Vector4(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) {}
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

	XMVECTOR GetValue() { return XMVectorSet(static_cast<float>(X), static_cast<float>(Y), static_cast<float>(Z), static_cast<float>(W)); }
	//////////////////////////////////////////////////////////////////////////////

public:
	double X = 0.0;
	double Y = 0.0;
	double Z = 0.0;
	double W = 0.0;
};