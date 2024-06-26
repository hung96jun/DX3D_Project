#include "CylinderShape.h"

CylinderShape::CylinderShape(const wstring ShaderFile)
	: Shape(ShaderFile)
{
	CONSTRUCTOR_DEBUG();

	TopRadius = 1.0f;
	BottomRadius = 1.0f;
	Height = 2.0f;

	StackCount = 20;
	SliceCount = 20;

	Create();
}

CylinderShape::~CylinderShape()
{
}

void CylinderShape::Create()
{
	vector<VertexMesh> vertices;

	float stackHeight = Height / static_cast<float>(StackCount);
	float radiusStep = (TopRadius - BottomRadius) / static_cast<float>(StackCount);

	UINT rightCount = StackCount + 1;
	for (UINT i = 0; i < rightCount; i++)
	{
		float y = -0.5f * Height + i * stackHeight;
		float r = BottomRadius + i * radiusStep;
		float theta = 2.0f * Math::PI / static_cast<float>(SliceCount);

		for (UINT j = 0; j <= SliceCount; j++)
		{
			float c = cosf(j * theta);
			float s = sinf(j * theta);

			VertexMesh v;
			v.Position = Vector3(r * c, y, r * s);
			v.Uv = Vector2(static_cast<float>(j) / static_cast<float>(SliceCount),
				1.0f - static_cast<float>(i) / static_cast<float>(StackCount));

			Vector3 tangent = Vector3(-s, 0.0f, c);
			v.Tangent = tangent;

			float dr = BottomRadius - TopRadius;
			Vector3 biTangent = Vector3(dr * c, -Height, dr * s);

			Vector3 normal;
			normal = Math::Cross(tangent, biTangent);
			v.Normal = normal.GetNormalize();

			vertices.push_back(v);
		}
	}

	vector<UINT> indices;
	UINT rightVertexCount = SliceCount + 1;
	for (UINT y = 0; y < StackCount; y++)
	{
		for (UINT x = 0; x < SliceCount; x++)
		{
			indices.push_back(y * rightVertexCount + x);
			indices.push_back((y + 1) * rightVertexCount + x);
			indices.push_back((y + 1) * rightVertexCount + (x + 1));

			indices.push_back(y * rightVertexCount + x);
			indices.push_back((y + 1) * rightVertexCount + x + 1);
			indices.push_back(y * rightVertexCount + x + 1);
		}
	}

	TopCap(vertices, indices);
	BottomCap(vertices, indices);

	SetVertices(vertices, indices);
}

void CylinderShape::GUIRender()
{
	SUPER::GUIRender();

}

void CylinderShape::TopCap(vector<VertexMesh>& Vertices, vector<UINT>& Indices)
{
	float y = 0.5f * Height;
	float theta = 2.0f * Math::PI / static_cast<float>(SliceCount);

	for (UINT i = 0; i <= SliceCount; i++)
	{
		float x = TopRadius * cosf(i * theta);
		float z = TopRadius * sinf(i * theta);

		float u = x / Height + 0.5f;
		float v = z / Height + 0.5f;

		Vertices.push_back(VertexMesh(x, y, z, u, v, 0.0f, 0.1f, 0.0f, 0.1f, 0.0f, 0.0f));
	}
	Vertices.push_back(VertexMesh(0.0f, y, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f));

	UINT baseIndex = static_cast<UINT>(Vertices.size()) - SliceCount - 2;
	UINT centerIndex = static_cast<UINT>(Vertices.size()) - 1;

	for (UINT i = 0; i < SliceCount; i++)
	{
		Indices.push_back(centerIndex);
		Indices.push_back(baseIndex + i + 1);
		Indices.push_back(baseIndex + i);
	}
}

void CylinderShape::BottomCap(vector<VertexMesh>& Vertices, vector<UINT>& Indices)
{
	float y = -0.5f * Height;
	float theta = 2.0f * Math::PI / static_cast<float>(SliceCount);

	for (UINT i = 0; i <= SliceCount; i++)
	{
		float x = BottomRadius * cosf(i * theta);
		float z = BottomRadius * sinf(i * theta);

		float u = x / Height + 0.5f;
		float v = z / Height + 0.5f;

		Vertices.push_back(VertexMesh(x, y, z, u, v, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	}
	Vertices.push_back(VertexMesh(0.0f, y, 0.0f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f));

	UINT baseIndex = static_cast<UINT>(Vertices.size()) - SliceCount - 2;
	UINT centerIndex = static_cast<UINT>(Vertices.size()) - 1;

	for (UINT i = 0; i < SliceCount; i++)
	{
		Indices.push_back(centerIndex);
		Indices.push_back(baseIndex + i);
		Indices.push_back(baseIndex + i + 1);
	}
}
