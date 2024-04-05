#pragma once
#include "Projection.h"

class Perspective :  public Projection
{
public:
	Perspective() = delete;
	Perspective(float Width, float Height, float Zn = 0.1f, float Zf = 100.0f, float Fov = static_cast<float>(XM_PI * 0.25f));
	~Perspective();

	virtual void Set(const float Width, const float Height, const float Zn = 0.1f, const float Zf = 100.0f, const float Fov = static_cast<float>(XM_PI * 0.25f)) override;

private:
	float Aspect;
};

