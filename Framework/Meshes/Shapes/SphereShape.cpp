#include "SphereShape.h"

SphereShape::SphereShape(const wstring ShaderFile)
	: Shape(ShaderFile)
{
	Radius = 5.0f;

	StackCount = 20;
	SliceCount = 20;

	Create();
}

SphereShape::~SphereShape()
{
}

void SphereShape::Create()
{
	vector<VertexMesh> vertices;
	vertices.push_back(VertexMesh(0.0f, Radius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f));

	float piStep = Math::PI / StackCount;
	float thetaStep = Math::PI * 2.0f / SliceCount;

	for (UINT i = 0; i <= StackCount - 1; i++)
	{
		float pi = i * piStep;

		for (UINT j = 0; j <= SliceCount; j++)
		{
			float theta = j / thetaStep;

			Vector3 p = Vector3
			(
				(Radius * sinf(pi)) * cosf(theta),
				(Radius * cos(pi)),
				(Radius * sinf(pi)) * sinf(theta)
			);

			Vector3 n = p.GetNormalize();
			Vector2 uv = Vector2(theta / (Math::PI * 2), pi / Math::PI);

			Vector3 t = Vector3
			(
				-(Radius * sinf(pi) * sinf(theta)),
				0.0f,
				(Radius * sinf(pi) * cosf(theta))
			);
			t.Normalize();

			vertices.push_back(VertexMesh(p, uv, n, t));
		}
	}
	vertices.push_back(VertexMesh(0.0f, -Radius, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f));

	vector<UINT> indices;
	for (UINT i = 1; i <= SliceCount; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = SliceCount + 1;
	for (UINT i = 0; i < StackCount - 2; i++)
	{
		for (UINT j = 0; j < SliceCount; j++)
		{
			indices.push_back(baseIndex + i + ringVertexCount + j);
			indices.push_back(baseIndex + i + ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) + ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) + ringVertexCount + j);
			indices.push_back(baseIndex + i + ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) + ringVertexCount + j + 1);
		}
	}

	UINT southPoleIndex = static_cast<UINT>(vertices.size()) - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < SliceCount; i++)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

	SetVertices(vertices, indices);
}
//
//void SphereShape::Update()
//{
//}
//
//void SphereShape::Render()
//{
//}

void SphereShape::GUIRender()
{
	SUPER::GUIRender();

}
