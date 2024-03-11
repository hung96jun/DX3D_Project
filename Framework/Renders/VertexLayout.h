#pragma once

#include "Math/Vector.h"

struct Vertex
{
	Vertex()
		: Position(0, 0, 0) {}

	Vertex(double X, double Y, double Z)
		: Position(X, Y, Z) {}

	Vector3 Position;
};