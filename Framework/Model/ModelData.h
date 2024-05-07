#pragma once

#include "Libraries.h"
#include "Renders/VertexLayout.h"

typedef VertexUVNormalTangentBlend ModelVertex;

struct MeshData
{
	string Name;
	UINT MaterialIndex;

	vector<ModelVertex> Vertices;
	vector<UINT> Indices;
};

struct NodeData
{
	int Index;
	string Name;
	int Parent;
	Matrix Transform;
};

struct BoneData
{
	int Index;
	string Name;
	Matrix Offset;
};

struct VertexWeights
{
	UINT Indices[4] = {};
	float Weights[4] = {};

	void Add(const UINT& Index, const float& Weight)
	{
		for (int i = 0; i < 4; i++)
		{
			if (Weights[i] == 0.0f)
			{
				Indices[i] = Index;
				Weights[i] = Weight;
				return;
			}
		}
	}

	void Normalize()
	{
		float Sum = 0.0f;
		for (int i = 0; i < 4; i++)
			Sum += Weights[i];
		for (int i = 0; i < 4; i++)
			Weights[i] /= Sum;
	}
};

struct KeyTransform
{
	Float3 Scale;
	Float4 Rotation;
	Float3 Position;
};

struct KeyFrame
{
	string BoneName;
	vector<KeyTransform> Transform;
};

struct ClipNode
{
	aiString Name;
	vector<KeyTransform> Transform;
};

struct Clip
{
	string Name;
	UINT FrameCount;
	float TickPerSec;
	vector<KeyFrame*> KeyFrame;
};

struct ClipTransform
{
	Matrix Transform[MAX_FRAME][MAX_BONE];
};