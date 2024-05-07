#pragma once
#include "Math/Vector.h"


/**
* Position
*/
struct Vertex
{
	Float3 Position;

	Vertex() : Position(0.0f, 0.0f, 0.0f) {}
	Vertex(float X, float Y, float Z) : Position(X, Y, Z) {}
	Vertex(Float3 Pos) : Position(Pos) {}
};

/**
* Position, Color
*/
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

/**
* Position, Uv
*/
struct VertexUV
{
	Float3 Position;
	Float2 Uv;

	VertexUV() : Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f) {}
	VertexUV(float X, float Y, float Z, float U, float V)
		: Position(X, Y, Z), Uv(U, V) {}
	VertexUV(Float3 Pos, Float2 Uv)
		: Position(Pos), Uv(Uv) {}
};

/**
* Position, Uv, Normal
*/
struct VertexUVNormal
{
	Float3 Position;
	Float2 Uv;
	Float3 Normal;

	VertexUVNormal() : Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f), Normal(0.0f, 0.0f, 0.0f) {}
	VertexUVNormal(float X, float Y, float Z, float U, float V, float NX, float NY, float NZ)
		: Position(X, Y, Z), Uv(U, V), Normal(NX, NY, NZ) {}
	VertexUVNormal(Float3 Pos, Float2 Uv, Float3 Normal)
		: Position(Pos), Uv(Uv), Normal(Normal) {}
};

/**
* Position, Uv, Normal, Tangent
*/
struct VertexUVNormalTangent
{
	Float3 Position;
	Float2 Uv;
	Float3 Normal;
	Float3 Tangent;

	VertexUVNormalTangent()
		: Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f), Normal(0.0f, 0.0f, 0.0f), Tangent(0.0f, 0.0f, 0.0f) {}
	VertexUVNormalTangent(float X, float Y, float Z, float U, float V, float NX, float NY, float NZ,
		float TX, float TY, float TZ)
		: Position(X, Y, Z), Uv(U, V), Normal(NX, NY, NZ), Tangent(TX, TY, TZ) {}
	VertexUVNormalTangent(Float3 Pos, Float2 Uv, Float3 Normal, Float3 Tangent)
		: Position(Pos), Uv(Uv), Normal(Normal), Tangent(Tangent) {}
};

/**
* Position, Uv, Normal, Tangent, Alpha
*/
struct VertexUVNormalTangentAlpha
{
	Float3 Position;
	Float2 Uv;
	Float3 Normal;
	Float3 Tangent;
	float Alpha[4];

	VertexUVNormalTangentAlpha()
		: Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f), Normal(0.0f, 0.0f, 0.0f), Tangent(0.0f, 0.0f, 0.0f) {}
	VertexUVNormalTangentAlpha(float X, float Y, float Z, float U, float V, float NX, float NY, float NZ,
		float TX, float TY, float TZ)
		: Position(X, Y, Z), Uv(U, V), Normal(NX, NY, NZ), Tangent(TX, TY, TZ) {}
	VertexUVNormalTangentAlpha(Float3 Pos, Float2 Uv, Float3 Normal, Float3 Tangent, float* Alpha)
		: Position(Pos), Uv(Uv), Normal(Normal), Tangent(Tangent)
	{
		for (int i = 0; i < 4; i++)
			this->Alpha[i] = Alpha[i];
	}
};

/**
* Position, Uv, Normal, Tangent, INdices, Weights
*/
struct VertexUVNormalTangentBlend
{
	Float3 Position;
	Float2 Uv;
	Float3 Normal;
	Float3 Tangent;
	Float4 Indices;
	Float4 Weights;

	VertexUVNormalTangentBlend()
		: Position(0.0f, 0.0f, 0.0f), Uv(0.0f, 0.0f), Normal(0.0f, 0.0f, 0.0f), Tangent(0.0f, 0.0f, 0.0f),
			Indices(0.0f, 0.0f, 0.0f, 0.0f), Weights(0.0f, 0.0f, 0.0f, 0.0f) {}
	VertexUVNormalTangentBlend(float X, float Y, float Z, float U, float V, float NX, float NY, float NZ,
		float TX, float TY, float TZ, float IX, float IY, float IZ, float IW, float WX, float WY, float WZ, float WW)
		: Position(X, Y, Z), Uv(U, V), Normal(NX, NY, NZ), Tangent(TX, TY, TZ),
			Indices(IX, IY, IZ, IW), Weights(WX, WY, WZ, WW) {}
	VertexUVNormalTangentBlend(Float3 Pos, Float2 Uv, Float3 Normal, Float3 Tangent, Float4 Indices, Float4 Weights)
		: Position(Pos), Uv(Uv), Normal(Normal), Tangent(Tangent), Indices(Indices), Weights(Weights) {}
};

struct InstanceData
{
	Matrix World;
	int Index;

	InstanceData() : World(XMMatrixIdentity()), Index(0) {}
	InstanceData(Matrix World, int Index) : World(World), Index(Index) {}
};