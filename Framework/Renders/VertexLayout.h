#pragma once
#include "Math/Vector.h"

struct Vertex
{
	Vector3 Pos;

	Vertex() : Pos(0.0f, 0.0f, 0.0f) {}
	Vertex(float X, float Y, float Z) : Pos(X, Y, Z) {}
	Vertex(Vector3 Position) : Pos(Position) {}
};

struct VertexColor
{
	Vector3 Pos;
	Float4 Color;

	VertexColor() : Pos(0.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f, 1.0f) {}
	VertexColor(float X, float Y, float Z, float R, float G, float B, float A = 1.0f)
		: Pos(X, Y, Z), Color(R, G, B, A) {}
	VertexColor(Vector3 Position, Float4 Color)
		:Pos(Position), Color(Color) {}
};