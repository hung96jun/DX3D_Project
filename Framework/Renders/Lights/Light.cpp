#include "Light.h"

Light::Light()
{
}

Light::~Light()
{
	SAFE_DELETE(LightBuffer);
}
