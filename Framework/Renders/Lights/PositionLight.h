#pragma once
#include "Light.h"

class PositionLight : public Light
{
public:
	PositionLight();
	~PositionLight();

	void Initialize() override;
	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}
	void GUIRender() override;

	Vector3& GetPosition() { return Position; }

protected:
	Transformation Transform;

	Vector3 Position = Vector3(0.0f);
};

