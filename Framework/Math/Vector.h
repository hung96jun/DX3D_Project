#pragma once
#include "Framework.h"

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

	XMVECTOR GetValue() { return XMVectorSet((float)X, (float)Y, 0.0f, 0.0f); }

public:
	double X;
	double Y;
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
	const bool operator==(const Vector3& Value)
	{
		return (X == Value.X && Y == Value.Y && Z == Value.Z);
	}
	const bool operator!=(const Vector3& Value)
	{
		return (X != Value.X || Y != Value.Y || Z != Value.Z);
	}

	Vector3& operator=(const Float3& Value)
	{
		X = Value.x;
		Y = Value.y;
		Z = Value.z;

		return *this;
	}

	const Vector3 operator+(const double& Value) const { return Vector3(X + Value, Y + Value, Z + Value); }
	const Vector3 operator-(const double& Value) const { return Vector3(X - Value, Y - Value, Z - Value); }
	const Vector3 operator+(const Vector3& Value) const { return Vector3(X + Value.X, Y + Value.Y, Z + Value.Z); }
	const Vector3 operator-(const Vector3& Value) const { return Vector3(X - Value.X, Y - Value.Y, Z - Value.Z); }
	const Vector3 operator*(const double& Value) const { return Vector3(X * Value, Y * Value, Z * Value); }
	const Vector3 operator/(const double& Value) const { return Vector3(X / Value, Y / Value, Z / Value); }

	Vector3& operator+=(const double& Value)
	{
		X += Value;
		Y += Value;
		Z += Value;

		return *this;
	}
	Vector3& operator-=(const double& Value)
	{
		X -= Value;
		Y -= Value;
		Z -= Value;

		return *this;
	}
	Vector3& operator+=(const Vector3& Value)
	{
		X += Value.X;
		Y += Value.Y;
		Z += Value.Z;

		return *this;
	}
	Vector3& operator-=(const Vector3& Value)
	{
		X -= Value.X;
		Y -= Value.Y;
		Z -= Value.Z;

		return *this;
	}
	Vector3& operator*=(const double& Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;

		return *this;
	}
	Vector3& operator/=(const double& Value)
	{
		X /= Value;
		Y /= Value;
		Z /= Value;

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
	//////////////////////////////////////////////////////////////////////////////

	XMVECTOR GetValue() { return XMVectorSet((float)X, (float)Y, (float)Z, 0.0f); }

public:
	double X;
	double Y;
	double Z;
};