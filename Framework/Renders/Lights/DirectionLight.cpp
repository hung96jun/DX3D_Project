#include "DirectionLight.h"

DirectionLight::DirectionLight()
{
	LightBuffer = new ConstBuffer(&Desc, sizeof(DirectionLightDesc));
}

DirectionLight::~DirectionLight()
{
}

void DirectionLight::Initialize()
{
}

void DirectionLight::Update()
{
}

void DirectionLight::Render()
{
	//LightBuffer->SetPS();
}
