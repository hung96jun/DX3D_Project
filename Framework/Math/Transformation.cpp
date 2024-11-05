#include "Libraries.h"
#include "Transformation.h"

Transformation::Transformation()
{
	World = XMMatrixIdentity();
}

Transformation::Transformation(Vector3 P, Vector3 R, Vector3 S)
{
	World = XMMatrixIdentity();
}

Transformation::~Transformation()
{
}

void Transformation::Update()
{
	/*
	* Y축 회전이 로컬 기준이 아닌 월드 기준으로 회전
	* Y축 회전은 월드 기준 회전이 맞는 것 같다. 상황에 따라 다르겠지만 unreal에서는 그렇다.
	*/
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

void Transformation::Update(Matrix OffsetWorld)
{
	World = XMMatrixTransformation(Pivot.GetValue(),
		XMQuaternionIdentity(), Scale.GetValue(), Pivot.GetValue(),
		XMQuaternionRotationRollPitchYawFromVector(Rotation.GetValue()),
		Position.GetValue());

	World *= OffsetWorld;

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

void Transformation::GUIRender()
{
	if (ImGui::TreeNode((Tag + "_Transform").c_str()))
	{
		static float sensitive = 0.01f;
		ImGui::DragFloat("Drag Sensitive", &sensitive, 0.01f, 0.0f);

		string log = "";
		log = "Global_Pos : " + GPosition.ToString();
		log += "\nGlobal_Scale : " + GScale.ToString();
		ImGui::Text(log.c_str());

		float pos[3];
		pos[0] = Position.X;
		pos[1] = Position.Y;
		pos[2] = Position.Z;
		ImGui::DragFloat3("Pos", pos, sensitive);
		SetPosition(Vector3(pos[0], pos[1], pos[2]));

		float scale[3];
		scale[0] = Scale.X;
		scale[1] = Scale.Y;
		scale[2] = Scale .Z;
		ImGui::DragFloat3("Scale", scale, sensitive);
		SetScale(Vector3(scale[0], scale[1], scale[2]));

		float rot[3];
		rot[0] = Rotation.X;
		rot[1] = Rotation.Y;
		rot[2] = Rotation.Z;
		ImGui::DragFloat3("Rotation", rot, sensitive);
		SetRotation(Vector3(rot[0], rot[1], rot[2]));

		Update();

		ImGui::TreePop();
	}
}
