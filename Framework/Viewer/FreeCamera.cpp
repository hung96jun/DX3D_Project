#include "FreeCamera.h"
#include "Systems/Time.h"
#include "Systems/Mouse.h"
#include "Systems/Keyboard.h"
#include "Utilities/BinaryWrite.h"
#include "Utilities/BinaryRead.h"

FreeCamera::FreeCamera()
{
	CONSTRUCTOR_DEBUG();
}

FreeCamera::~FreeCamera()
{
	DESTRUCTOR_DEBUG();
}

void FreeCamera::Update()
{
	SUPER::Update();

	Vector3 forward = GetForward();
	Vector3 up = GetUp();
	Vector3 right = GetRight();

	Vector3 pos = Vector3::ZeroVector();

	if (Mouse::Get()->GetMouseWheel() > 0)
	{
		pos += forward * Move * Time::Get()->GetDeltaTime() * WheelMove;
		SetPosition(GetPosition() + pos);
	}
	else if (Mouse::Get()->GetMouseWheel() < 0)
	{
		pos += -forward * Move * Time::Get()->GetDeltaTime() * WheelMove;
		SetPosition(GetPosition() + pos);
	}

	if (Mouse::Get()->IsPress(1) == false) return;

	// Move
	{

		if (Keyboard::Get()->IsPress('W'))
			pos += forward * Move * Time::Get()->GetDeltaTime();
		else if (Keyboard::Get()->IsPress('S'))
			pos += -forward * Move * Time::Get()->GetDeltaTime();

		if (Keyboard::Get()->IsPress('D'))
			pos += right * Move * Time::Get()->GetDeltaTime();
		else if (Keyboard::Get()->IsPress('A'))
			pos += -right * Move * Time::Get()->GetDeltaTime();

		if (Keyboard::Get()->IsPress('E'))
			pos += up * Move * Time::Get()->GetDeltaTime();
		else if(Keyboard::Get()->IsPress('Q'))
			pos += -up * Move * Time::Get()->GetDeltaTime();

		SetPosition(GetPosition() + pos);
	}

	// Rotation
	{
		Vector3 rot, value;
		value = Mouse::Get()->GetMouseMoveValue();

		rot.X += value.Y * Rotation * Time::Get()->GetDeltaTime();
		rot.Y += value.X * Rotation * Time::Get()->GetDeltaTime();
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
	ImGui::DragFloat("Camera WheelMove", &WheelMove, 0.1f, 0.0f);
	ImGui::DragFloat("Camera Rotation", &Rotation, 0.01f, 0.0f);

	string debug = "";
	debug += "\nPos : " + Transform.GetPosition().ToString();
	debug += "\nRot : " + Transform.GetRotation().ToString();
	ImGui::Text(debug.c_str());

	if (ImGui::Button("Save"))
	{
		DIALOG->OpenDialog("SaveFolder", "FindFolder", ".so", "../Datas/Binary/");
	}

	if (DIALOG->Display("SaveFolder"))
	{
		if (DIALOG->IsOk())
		{
			string path = DIALOG->GetFilePathName();
			BinaryWrite* writer = new BinaryWrite(path);

			writer->WriteFloat(Move);
			writer->WriteFloat(Rotation);

			delete writer;
		}

		DIALOG->Close();
	}

	ImGui::SameLine();

	if (ImGui::Button("Load"))
	{
		DIALOG->OpenDialog("LoadFolder", "FindFolder", ".so", "../Datas/Binary/");
	}

	if (DIALOG->Display("LoadFolder"))
	{
		if (DIALOG->IsOk())
		{
			string str = DIALOG->GetFilePathName();
			wstring path(str.begin(), str.end());
			BinaryRead* reader = new BinaryRead(ToString(path));

			Move = reader->ReadFloat();
			Rotation = reader->ReadFloat();

			delete reader;
		}
		DIALOG->Close();
	}

	ImGui::End();
}
