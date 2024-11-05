#pragma once
#include "Light.h"

struct DirectionLightDesc
{
	DirectionLightDesc();
	DirectionLightDesc(const Color Ambient, const Color Diffuse, const Color Specualar, const Vector3 Direction)
		: Ambient(Ambient), Diffuse(Diffuse), Specular(Specular), Direction(Direction) {}

public:
	Color Ambient = Color(0.0f);
	Color Diffuse = Color(0.0f);
	Color Specular = Color(0.0f);
	Vector3 Direction = Vector3(Direction);
private:
	float Padding;
};

class DirectionLight : public Light
{
public:
	DirectionLight();
	~DirectionLight();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void GUIRender() override {}

private:
	DirectionLightDesc Desc;
};

