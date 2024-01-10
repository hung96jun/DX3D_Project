#pragma once
#include "Projection.h"

class Orthgraphic : public Projection
{
public:
	Orthgraphic(const float width, const float height, const float zn = 0.1f, const float zf = 1000.0f);
	~Orthgraphic();

	void Set(const float width, const float height, const float zn = 0.1f, const float zf = 1000.0f, const float fov = 0.0f) override;
};

