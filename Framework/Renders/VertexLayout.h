#pragma once
#include "Math/Vector.h"

struct Vertex
{
	Float3 Position;

	Vertex() : Position(0.0f, 0.0f, 0.0f) {}
	Vertex(float X, float Y, float Z) : Position(X, Y, Z) {}
	Vertex(Float3 Pos) : Position(Pos) {}
};

struct VertexColor
{
	Float3 Position;
	Float4 Color;

	VertexColor() : Position(0.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f, 1.0f) {}
	VertexColor(float X, float Y, float Z, float R, float G, float B, float A = 1.0f)
		: Position(X, Y, Z), Color(R, G, B, A) {}
	VertexColor(Float3 Pos, Float4 Color)
		:Position(Pos), Color(Color) {}
};

struct VertexTexture
{
	Float3 Position;
	Float2 Uv;

	VertexTexture() : Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f) {}
	VertexTexture(float X, float Y, float Z, float U, float V)
		:Position(X, Y, Z), Uv(U, V) {}
	VertexTexture(Float3 Pos, Float2 Uv)
		:Position(Pos), Uv(Uv) {}
};