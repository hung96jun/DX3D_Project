#pragma once

#include "Framework/Buffers/GlobalBuffer.h"
#include "Math/Transformation.h"
#include "Utilities/Debug.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update() = 0;
	virtual void GUIRender() = 0;

	void SetPosition(const float X, const float Y, const float Z);
	void SetPosition(const Vector3& Vec);

	void SetRotation(const float X, const float Y, const float Z);
	void SetRotation(const Vector3& Vec);

	void SetRotationDegree(const float X, const float Y, const float Z);
	void SetRotationDegree(const Vector3& Vec);

	const Vector3& GetPosition() const { return Position; }
	const Vector3& GetRotation() const { return Rotation; }
	const Vector3 GetRotationDegree() const { return Vector3(Rotation * 57.29577957f); }

	void GetMatrix(Matrix* Mat);
	void Set();

	Vector3 GetForward() { return Forward; }
	Vector3 GetUp() { return Up; }
	Vector3 GetRight() { return Right; }

protected:
	virtual void ApplyRotation();
	virtual void ApplyMove();

	void View();

protected:
	Transformation Transform;

private:
	/* ViewBuffer */
	ViewBuffer* VBuffer = nullptr;

	Vector3 Position = Vector3::ZeroVector();
	Vector3 Rotation = Vector3::ZeroVector();

	Vector3 Forward = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 Right = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 Up = Vector3(1.0f, 0.0f, 0.0f);

	Matrix MatRotation;
	//Matrix MatView;
	Matrix MatView;
};

