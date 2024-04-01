#include "Libraries.h"
#include "Transformation.h"

Transformation::Transformation()
{
	Pivot = Vector3();
	Position = Vector3();
	Rotation = Vector3();
	Scale = Vector3();

	World = XMMatrixIdentity();
}

Transformation::Transformation(Vector3 P, Vector3 R, Vector3 S)
{
	Pivot = Vector3();
	Position = P;
	Rotation = R;
	Scale = S;

	World = XMMatrixIdentity();
}

Transformation::~Transformation()
{
}

void Transformation::Update()
{
	World = XMMatrixTransformation(Pivot.GetValue(),
		XMQuaternionIdentity(), Scale.GetValue(), Pivot.GetValue(),
		XMQuaternionRotationRollPitchYawFromVector(Rotation.GetValue()),
		Position.GetValue());

	if (Parent != nullptr)
		World *= Parent->World;

	XMStoreFloat4x4(&MatWorld, World);
	Right = Vector3(MatWorld._11, MatWorld._12, MatWorld._13);
	Up = Vector3(MatWorld._21, MatWorld._22, MatWorld._23);
	Forward = Vector3(MatWorld._31, MatWorld._32, MatWorld._33);

	XMVECTOR s, r, t;
	XMMatrixDecompose(&s, &r, &t, World);

	Float3 pos, rot, scale;
	XMStoreFloat3(&pos, t);
	XMStoreFloat3(&rot, r);
	XMStoreFloat3(&scale, s);

	GPosition = pos;
	GRotation = rot;
	GScale = scale;
}
