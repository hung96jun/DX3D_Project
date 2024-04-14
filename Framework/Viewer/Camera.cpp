#include "Libraries.h"
#include "Camera.h"

Camera::Camera()
{
	MatRotation = XMMatrixIdentity();
	MatView = XMMatrixIdentity();

	ApplyRotation();
	ApplyMove();

	VBuffer = new ViewBuffer();
}

Camera::~Camera()
{
	SAFE_DELETE(VBuffer);
}

void Camera::Update()
{
	Transform.SetPosition(Position);
	Transform.SetRotation(Rotation);
	Transform.Update();
}

void Camera::SetPosition(const float X, const float Y, const float Z)
{
	Position = Vector3(X, Y, Z);
	ApplyMove();
}

void Camera::SetPosition(const Vector3& Vec)
{
	SetPosition(Vec.X, Vec.Y, Vec.Z);
}

void Camera::SetRotation(const float X, const float Y, const float Z)
{
	Rotation = Vector3(X, Y, Z);
	ApplyRotation();
}

void Camera::SetRotation(const Vector3& Vec)
{
	SetRotation(Vec.X, Vec.Y, Vec.Z);
}

void Camera::SetRotationDegree(const float X, const float Y, const float Z)
{
	Rotation = Vector3(X, Y, Z) * 0.01745328f;
}

void Camera::SetRotationDegree(const Vector3& Vec)
{
	SetRotationDegree(Vec.X, Vec.Y, Vec.Z);
}

void Camera::GetMatrix(Matrix* Mat)
{
	//memcpy(Mat, &MatView, sizeof(Matrix));
	memcpy(Mat, &Transform.GetWorld(), sizeof(Matrix));
}

void Camera::Set()
{
	Transform.Update();
	MatView = XMMatrixInverse(nullptr, Transform.GetWorld());
	VBuffer->Set(MatView, Transform.GetWorld());
	VBuffer->SetVS(1);
}

void Camera::ApplyRotation()
{
	Matrix x, y, z;
	x = XMMatrixRotationX(Rotation.X);
	y = XMMatrixRotationY(Rotation.Y);
	z = XMMatrixRotationZ(Rotation.Z);

	MatRotation = x * y * z;

	Forward = XMVector3TransformNormal(Vector3(0.0f, 0.0f, 1.0f).GetValue(), MatRotation);
	Up = XMVector3TransformNormal(Vector3(0.0f, 1.0f, 0.0f).GetValue(), MatRotation);
	Right = XMVector3TransformNormal(Vector3(1.0f, 0.0f, 0.0f).GetValue(), MatRotation);
}

void Camera::ApplyMove()
{
	View();
}

void Camera::View()
{
	XMMatrixLookAtLH(Position.GetValue(), (Position + Forward).GetValue(), Up.GetValue());
}
