#pragma once

#include "PositionLight.h"

struct PointLightDesc
{
public:
	Color Ambient = Color(0.0f);
	Color Diffuse = Color(0.0f);
	Color Specular = Color(0.0f);
	Color Emissive = Color(0.0f);

	Vector3 Position = Vector3(0.0f);
	float Range = 0.0f;

	float Intensity = 0.0f;
private:
	float Padding[3];
};

class PointLight : public PositionLight
{
public:
	PointLight();
	~PointLight();

	void Initialize() final {}
	void Update() final;
	void PreRender() final {}
	void Render() final;
	void PostRender() final {}
	void GUIRender() final {}

	Color& GetDiffuse() { return Diffuse; }
	Color& GetEmissive() { return Emissive; }
	float& GetRange() { return Range; }
	float& GetIntensity() { return Intensity; }

private:
	PointLightDesc Desc;

	Color Diffuse;
	Color Emissive;

	float Range;
	float Intensity;
};

