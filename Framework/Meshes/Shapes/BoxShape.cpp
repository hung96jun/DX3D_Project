#include "BoxShape.h"

BoxShape::BoxShape(const wstring ShaderFile)
	: Shape(ShaderFile)
{
	CONSTRUCTOR_DEBUG();

	X = Y = Z = 1.0f;

	Create();
}

BoxShape::~BoxShape()
{
	DESTRUCTOR_DEBUG();

}

void BoxShape::Create()
{
	vector<VertexMesh> vertices;
	vector<UINT> indices;

	vertices.resize(4 * 6);
	{
		// Front
		vertices[0].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[1].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[2].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[3].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[0].Uv = Vector2(0.0f, 1.0f);
		vertices[1].Uv = Vector2(0.0f, 0.0f);
		vertices[2].Uv = Vector2(1.0f, 1.0f);
		vertices[3].Uv = Vector2(1.0f, 0.0f);

		// Back
		vertices[4].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[5].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[6].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[7].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);

		vertices[4].Uv = Vector2(0.0f, 1.0f);
		vertices[5].Uv = Vector2(0.0f, 0.0f);
		vertices[6].Uv = Vector2(1.0f, 1.0f);
		vertices[7].Uv = Vector2(1.0f, 0.0f);

		// Left
		vertices[8].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[9].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[10].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[11].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);

		vertices[8].Uv = Vector2(0.0f, 1.0f);
		vertices[9].Uv = Vector2(0.0f, 0.0f);
		vertices[10].Uv = Vector2(1.0f, 1.0f);
		vertices[11].Uv = Vector2(1.0f, 0.0f);


		// Right
		vertices[12].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[13].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[14].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[15].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[12].Uv = Vector2(0.0f, 1.0f);
		vertices[13].Uv = Vector2(0.0f, 0.0f);
		vertices[14].Uv = Vector2(1.0f, 1.0f);
		vertices[15].Uv = Vector2(1.0f, 0.0f);

		// Top
		vertices[16].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[17].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[18].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[19].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[16].Uv = Vector2(0.0f, 1.0f);
		vertices[17].Uv = Vector2(0.0f, 0.0f);
		vertices[18].Uv = Vector2(1.0f, 1.0f);
		vertices[19].Uv = Vector2(1.0f, 0.0f);

		// Top
		vertices[20].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[21].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[22].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[23].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);

		vertices[20].Uv = Vector2(0.0f, 1.0f);
		vertices[21].Uv = Vector2(0.0f, 0.0f);
		vertices[22].Uv = Vector2(1.0f, 1.0f);
		vertices[23].Uv = Vector2(1.0f, 0.0f);

		indices =
		{
			0, 1, 2, 2, 1, 3,
			4, 5, 6, 6, 5, 7,
			11, 9, 10, 10, 9, 8,
			15, 13, 14, 14, 13, 12,
			16, 17, 18, 18, 17, 19,
			20, 21, 22, 22, 21, 23
		};
	}

	SetVertices(vertices, indices);
}

//void BoxShape::Update()
//{
//	SUPER::Update();
//
//}
//
//void BoxShape::Render()
//{
//	SUPER::Render();
//
//}

void BoxShape::GUIRender()
{
	SUPER::GUIRender();

}
