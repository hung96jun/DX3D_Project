#pragma once

#include "Math/Vector.h"

class Transformation
{
public:
	Transformation();
	Transformation(Vector3 P, Vector3 R = Vector3::ZeroVector(), Vector3 S = Vector3::ZeroVector());
	~Transformation();

	void Update();
	void GUIRender();

	const Vector3 GetRight() const { return Right.GetNormalize(); }
	const Vector3 GetUp() const { return Up.GetNormalize(); }
	const Vector3 GetForward() const { return Forward.GetNormalize(); }
	const Vector3 GetLeft() const { return Vector3(Right * -1.0f).GetNormalize(); }
	const Vector3 GetDown() const { return Vector3(Up * -1.0f).GetNormalize(); }
	const Vector3 GetBack() const { return Vector3(Forward * -1.0f).GetNormalize(); }

	void SetActive(const bool Value) { bActive = Value; }
	const bool IsActive() const 
	{ 
		if (Parent != nullptr && Parent->IsActive() == false)
			return false;

		return bActive;
	}

	Matrix& GetWorld() { return World; }

	void SetOwner(Transformation* Parent) { this->Parent = Parent; }
	void SetPivot(const Vector3 Pivot) { this->Pivot = Pivot; }
	Vector3 GetPivot() const { return Pivot; }

	Vector3 GetPosition() const { return Position; }
	Vector3 GetRotation() const { return Rotation; }
	Vector3 GetScale() const { return Scale; }

	const Vector3 GetGlobalPosition() const { return GPosition; }
	const Vector3 GetGlobalRotation() const { return GRotation; }
	const Vector3 GetGlobalScale() const { return GScale; }

	void SetPosition(const Vector3 Value) { Position = Value; }
	void SetRotation(const Vector3 Value) { Rotation = Value; }
	void SetScale(const Vector3 Value) { Scale = Value; }

	void SetTag(const string Tag) { this->Tag = Tag; }
	const string& GetTag() const { return Tag; }

	string ToString() const 
	{
		string result;

		result += "{ " + to_string(World.r[0].m128_f32[0]) + ", " + to_string(World.r[0].m128_f32[1]) + ", " + to_string(World.r[0].m128_f32[2]) + ", " + to_string(World.r[0].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[1].m128_f32[0]) + ", " + to_string(World.r[1].m128_f32[1]) + ", " + to_string(World.r[1].m128_f32[2]) + ", " + to_string(World.r[1].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[2].m128_f32[0]) + ", " + to_string(World.r[2].m128_f32[1]) + ", " + to_string(World.r[2].m128_f32[2]) + ", " + to_string(World.r[2].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[3].m128_f32[0]) + ", " + to_string(World.r[3].m128_f32[1]) + ", " + to_string(World.r[3].m128_f32[2]) + ", " + to_string(World.r[3].m128_f32[3]) + " }";

		return result;
	}

	static string ToString(const Matrix World)
	{
		string result;

		result += "{ " + to_string(World.r[0].m128_f32[0]) + ", " + to_string(World.r[0].m128_f32[1]) + ", " + to_string(World.r[0].m128_f32[2]) + ", " + to_string(World.r[0].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[1].m128_f32[0]) + ", " + to_string(World.r[1].m128_f32[1]) + ", " + to_string(World.r[1].m128_f32[2]) + ", " + to_string(World.r[1].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[2].m128_f32[0]) + ", " + to_string(World.r[2].m128_f32[1]) + ", " + to_string(World.r[2].m128_f32[2]) + ", " + to_string(World.r[2].m128_f32[3]) + " }";
		result += "\n{ " + to_string(World.r[3].m128_f32[0]) + ", " + to_string(World.r[3].m128_f32[1]) + ", " + to_string(World.r[3].m128_f32[2]) + ", " + to_string(World.r[3].m128_f32[3]) + " }";

		return result;
	}

private:
	string Tag = "";

	Matrix World;
	Transformation* Parent = nullptr;

	Vector3 Pivot = Vector3::ZeroVector();

	// Local
	Vector3 Position = Vector3::ZeroVector();
	Vector3 Rotation = Vector3::ZeroVector();
	Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);

	// Global
	Vector3 GPosition = Vector3::ZeroVector();
	Vector3 GRotation = Vector3::ZeroVector();
	Vector3 GScale = Vector3(1.0f, 1.0f, 1.0f);

	Vector3 Forward = Vector3::ZeroVector();
	Vector3 Right = Vector3::ZeroVector();
	Vector3 Up = Vector3::ZeroVector();

	Float4x4 MatWorld;

	bool bActive = true;
};