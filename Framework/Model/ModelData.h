#pragma once
#include "Renders/VertexLayout.h"

typedef VertexUVNormalTangentBlend VertexModel;

struct BoneData
{
	int Index;
	string Name;
	int Parent;
	Matrix Transform;
};

struct MeshPart
{
	string MaterialName;

	UINT StartVertex;
	UINT VertexCount;

	UINT StartIndex;
	UINT IndexCount;
};

struct MeshData
{
	int BoneIndex;

	vector<VertexModel> Vertices;
	vector<UINT> Indices;

	vector<MeshPart*> MeshParts;
};

struct MaterialData
{
	string Name;

	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	string DiffuseFile;
	string SpecularFile;
	string NormalFile;
};

struct BlendWeight
{
	Vector4 Indices = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 Weights = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

	void Set(const UINT Index, const UINT BoneIndex, const float Weight)
	{
		float i = static_cast<float>(BoneIndex);
		float w = Weight;

		switch (Index)
		{
			case 0: Indices.X = i; Weights.X = w; break;
			case 1: Indices.Y = i; Weights.Y = w; break;
			case 2: Indices.Z = i; Weights.Z = w; break;
			case 3: Indices.W = i; Weights.W = w; break;
		}
	}
};

struct BoneWeight
{
private:
	typedef pair<int, float> Pair;
	vector<Pair> BoneWeights;

public:
	void AddWeights(UINT BoneIndex, float BoneWeights)
	{
		if (BoneWeights <= 0.0f) return;

		bool bAdd = false;
		vector<Pair>::iterator it = this->BoneWeights.begin();
		while (it != this->BoneWeights.end())
		{
			if (BoneWeights > it->second)
			{
				this->BoneWeights.insert(it, Pair(BoneIndex, BoneWeights));
				bAdd = true;

				break;
			}

			it++;
		}

		if (bAdd == false)
			this->BoneWeights.push_back(Pair(BoneIndex, BoneWeights));
	}

	void GetBlendWeights(BlendWeight& BlendWeights)
	{
		for (UINT i = 0; i < this->BoneWeights.size(); i++)
		{
			if (i >= 4) return;
			BlendWeights.Set(i, BoneWeights[i].first, BoneWeights[i].second);
		}
	}

	void Normalize()
	{
		float totalWeights = 0.0f;
		int i = 0;
		vector<Pair>::iterator it = BoneWeights.begin();
		while (it != BoneWeights.end())
		{
			if (i < 4)
			{
				totalWeights += it->second;
				i++; it++;
			}
			else
				it = BoneWeights.erase(it);

			float scale = 1.0f / totalWeights;

			it = BoneWeights.begin();
			while (it != BoneWeights.end())
			{
				it->second *= scale;
				it++;
			}
		}
	}
};

struct KeyFrameData
{
	float Frame;

	Vector3 Scale;
	Vector3 Rotation;
	Vector3 Position;
};

struct KeyFrame
{
	string BoneName;
	vector<KeyFrameData> Positions;
};

struct Clip
{
	string Name;

	UINT FrameCount;
	float FrameRate;

	vector<KeyFrame> KeyFrames;
};

struct ClipNode
{
	aiString Name;
	vector<KeyFrameData> KeyFrames;
};