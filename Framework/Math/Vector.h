#pragma once
#include "Libraries.h"

struct Vector2
{
public:
	Vector2() : X(0.0f), Y(0.0f) {}
	//Vector2(double Value) : X(static_cast<float>(Value)), Y(static_cast<float>(Value)) {}
	//Vector2(double X, double Y) : X(static_cast<float>(X)), Y(static_cast<float>(Y)) {}
	Vector2(float Value) : X(Value), Y(Value) {}
	Vector2(float X, float Y) : X(X), Y(Y) {}
	Vector2(XMVECTOR Value)
	{
		X = XMVectorGetX(Value);
		Y = XMVectorGetY(Value);
	}

	//////////////////////////////////////////////////////////////////////////////
	// operator overloading
	//////////////////////////////////////////////////////////////////////////////
	const bool operator==(const Vector2& Value) const { return (X == Value.X) && (Y == Value.Y); }
	const bool operator!=(const Vector2& Value) const { return (X != Value.X) || (Y != Value.Y); }
	
	Vector2 operator+(const float& Value) const { return Vector2(X + Value, Y + Value); }
	Vector2 operator-(const float& Value) const { return Vector2(X - Value, Y - Value); }
	Vector2 operator*(const float& Value) const { return Vector2(X * Value, Y * Value); }
	Vector2 operator/(const float& Value) const { return Vector2(X / Value, Y / Value); }
	Vector2 operator+(const Vector2& Value) const { return Vector2(X + Value.X, Y + Value.Y); }
	Vector2 operator-(const Vector2& Value) const { return Vector2(X - Value.X, Y - Value.Y); }

	operator Float2() const
	{
		return Float2(X, Y);
	}

	const Vector2 operator-() const { return Vector2(-X, -Y); }
	
	//Float2 operator=(const Vector2& Value)
	//{
	//	return Float2(Value.X, Value.Y);
	//}

	Vector2& operator+=(const float& Value)
	{
		X += Value;
		Y += Value;

		return *this;
	}
	Vector2& operator-=(const float& Value)
	{
		X -= Value;
		Y -= Value;

		return *this;
	}
	Vector2& operator*=(const float& Value)
	{
		X *= Value;
		Y *= Value;

		return *this;
	}
	Vector2& operator/=(const float& Value)
	{
		X /= Value;
		Y /= Value;

		return *this;
	}
	Vector2& operator+=(const Vector2& Value)
	{
		X += Value.X;
		Y += Value.Y;

		return *this;
	}
	Vector2& operator-=(const Vector2& Value)
	{
		X -= Value.X;
		Y -= Value.Y;

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
	Vector3(float N) : X(N), Y(N), Z(N) {}
	Vector3(float X, float Y, float Z) : X(X), Y(Y), Z(Z) {}
	Vector3(XMVECTOR Value)
	{
		X = XMVectorGetX(Value);
		Y = XMVectorGetY(Value);
		Z = XMVectorGetZ(Value);
	}
	Vector3(Float3 Value)
	{
		X = Value.x;
		Y = Value.y;
		Z = Value.z;
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

	Vector3& operator=(const float Value[3])
	{
		X = Value[0];
		Y = Value[1];
		Z = Value[2];

		return *this;
	}

	Vector3& operator=(const Float3& Value)
	{
		X = Value.x;
		Y = Value.y;
		Z = Value.z;

		return *this;
	}

	const Vector3 operator+(const float& Value) const { return Vector3(X + Value, Y + Value, Z + Value); }
	const Vector3 operator-(const float& Value) const { return Vector3(X - Value, Y - Value, Z - Value); }
	const Vector3 operator+(const Vector3& Value) const { return Vector3(X + Value.X, Y + Value.Y, Z + Value.Z); }
	const Vector3 operator-(const Vector3& Value) const { return Vector3(X - Value.X, Y - Value.Y, Z - Value.Z); }
	const Vector3 operator*(const float& Value) const { return Vector3(X * Value, Y * Value, Z * Value); }
	const Vector3 operator/(const float& Value) const { return Vector3(X / Value, Y / Value, Z / Value); }

	const Vector3 operator-() const { return Vector3(-X, -Y, -Z); }

	//Float3 operator=(const Vector3& Value)
	//{
	//	return Float3(Value.X, Value.Y, Value.Z);
	//}

	operator Float3() const 
	{
		return Float3(X, Y, Z);
	}

	Vector3& operator+=(const float& Value)
	{
		X += Value;
		Y += Value;
		Z += Value;

		return *this;
	}
	Vector3& operator-=(const float& Value)
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
	Vector3& operator*=(const float& Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;

		return *this;
	}
	Vector3& operator/=(const float& Value)
	{
		X /= Value;
		Y /= Value;
		Z /= Value;

		return *this;
	}

	Vector3& operator=(const XMVECTOR& Value)
	{
		X = XMVectorGetX(Value);
		Y = XMVectorGetY(Value);
		Z = XMVectorGetZ(Value);

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
	Vector4(float Value) : X(Value), Y(Value), Z(Value), W(Value) {}
	Vector4(float X, float Y, float Z, float W) : X(X), Y(Y), Z(Z), W(W) {}
	Vector4(XMVECTOR Value)
	{
		X = XMVectorGetX(Value);
		Y = XMVectorGetY(Value);
		Z = XMVectorGetZ(Value);
		W = XMVectorGetW(Value);
	}



	//////////////////////////////////////////////////////////////////////////////
	// functions
	//////////////////////////////////////////////////////////////////////////////
	static const Vector4 ZeroVector() { return Vector4(0.0, 0.0, 0.0, 0.0); }
	static const Vector4 Right() { return Vector4(1.0, 0.0, 0.0, 0.0); }
	static const Vector4 Up() { return Vector4(0.0, 1.0, 0.0, 0.0); }
	static const Vector4 Forward() { return Vector4(0.0, 0.0, 1.0, 0.0); }

	operator Float4() const
	{
		return Float4(X, Y, Z, W);
	}

	string ToString() const
	{
		return ("X : " + to_string(X) + ", Y : " + to_string(Y) + ", Z : " + to_string(Z) + ", W : " + to_string(W));
	}

	XMVECTOR GetValue() { return XMVectorSet(X, Y, Z, W); }
	//////////////////////////////////////////////////////////////////////////////

public:
	union
	{
		struct
		{
			float X, Y, Z, W;
		};

		struct
		{
			float R, G, B, A;
		};
	};
};

typedef Vector4 Color;