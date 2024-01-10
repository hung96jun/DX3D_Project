#pragma once

#include "Projection.h"

class Perspective : public Projection
{
public:
	Perspective(const float width, const float height, const float zn = 0.1f, const float zf = 1000.0f, const float fov = static_cast<float>(XM_PI * 0.25f));
	~Perspective();

	void Set(const float width, const float height, const float zn = 0.1f, const float zf = 1000.0f, const float fov = static_cast<float>(XM_PI * 0.25f)) override;

private:
	float Aspect;
};

