#pragma once

#include "Math/Vector.h"

class Transformation
{
public:
	Transformation();
	Transformation(Vector3 P, Vector3 R = Vector3::ZeroVector(), Vector3 S = Vector3::ZeroVector());
	~Transformation();

	void Update();

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

	void SetParent(Transformation* Parent) { this->Parent = Parent; }
	void SetPivot(const Vector3 Pivot) { this->Pivot = Pivot; }
	Vector3 GetPivot() const { return Pivot; }

	Vector3 GetPosition() const { return Position; }
	Vector3 GetRotation() const { return Rotation; }
	Vector3 GetScale() const { return Scale; }

	void SetPosition(const Vector3 Value) { Position = Value; }
	void SetRotation(const Vector3 Value) { Rotation = Value; }
	void SetScale(const Vector3 Value) { Scale = Value; }

private:
	Matrix World;
	Transformation* Parent = nullptr;

	Vector3 Pivot;

	// Local
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

	// Global
	Vector3 GPosition;
	Vector3 GRotation;
	Vector3 GScale;

	Vector3 Forward, Right, Up;

	Float4x4 MatWorld;

	bool bActive = true;
};