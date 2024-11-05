#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

void PointLight::Update()
{
	SUPER::Update();

	Desc.Ambient = Ambient;
	Desc.Diffuse = Diffuse;
	Desc.Specular = Specular;
	Desc.Emissive = Emissive;
	Desc.Position = Position;
	Desc.Range = Range;
	Desc.Intensity = Intensity;
}

void PointLight::Render()
{
}
