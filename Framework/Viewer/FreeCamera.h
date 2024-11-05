#pragma once
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera();
	~FreeCamera();

	void Update() override;
	void GUIRender() override;

	void SetSpeed(const float Move, const float Rotation = 2.0f);

private:
	float Move = 20.0f;
	float Rotation = 2.0f;
	float WheelMove = 20.0f;
};

