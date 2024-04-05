#pragma once

#include "Projection.h"

class Orthographic : public Projection
{
public:
	Orthographic() = delete;
	Orthographic(float Width, float Height, float Zn = 0.1f, float Zf = 1000.0f, float Fov = 0.0f);
	~Orthographic();

	virtual void Set(const float Width, const float Height, const float Zn = 0.1f, const float Zf = 1000.0f, const float Fov = 0.0f) override;

};

