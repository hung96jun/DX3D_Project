#include "FreeCamera.h"
#include "Systems/Time.h"
#include "Systems/Mouse.h"
#include "Systems/Keyboard.h"

FreeCamera::FreeCamera()
{
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Update()
{
	SUPER::Update();

	if (Mouse::Get()->IsPress(1) == false) return;

	Vector3 forward = GetForward();
	Vector3 up = GetUp();
	Vector3 right = GetRight();

	// Move
	{
		Vector3 pos = Vector3::ZeroVector();

		if (Keyboard::Get()->IsPress('W'))
			pos = forward * Move * Time::GetDeltaTime();
		else if (Keyboard::Get()->IsPress('S'))
			pos = -forward * Move * Time::GetDeltaTime();

		if (Keyboard::Get()->IsPress('D'))
			pos = right * Move * Time::GetDeltaTime();
		else if (Keyboard::Get()->IsPress('A'))
			pos = -right * Move * Time::GetDeltaTime();

		if (Keyboard::Get()->IsPress('E'))
			pos = up * Move * Time::GetDeltaTime();
		else if(Keyboard::Get()->IsPress('Q'))
			pos = -up * Move * Time::GetDeltaTime();

		SetPosition(GetPosition() + pos);
	}

	// Rotation
	{
		Vector3 rot, value;
		value = Mouse::Get()->GetWheelValue();

		rot.X += value.Y * Rotation * Time::GetDeltaTime();
		rot.Y += value.X * Rotation * Time::GetDeltaTime();
		rot.Z = 0.0f;

		SetRotation(GetRotation() + rot);
	}
}

void FreeCamera::SetSpeed(const float Move, const float Rotation)
{
	this->Move = Move;
	this->Rotation = Rotation;
}

void FreeCamera::GUIRender()
{
	ImGui::Begin("Camera");

	ImGui::DragFloat("Camera Move", &Move, 0.01f, 0.0f);
	ImGui::DragFloat("Camera Rotation", &Rotation, 0.01f, 0.0f);

	string debug = "";
	debug += "\nPos : " + Transform.GetPosition().ToString();
	debug += "\nRot : " + Transform.GetRotation().ToString();
	ImGui::Text(debug.c_str());

	ImGui::End();
}
