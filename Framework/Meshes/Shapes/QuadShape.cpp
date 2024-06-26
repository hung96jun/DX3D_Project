#include "QuadShape.h"

QuadShape::QuadShape(const wstring ShaderFile)
	: Shape(ShaderFile)
{
	CONSTRUCTOR_DEBUG();

	Size.X = Size.Y = 1.0f;
	Create();
}

QuadShape::~QuadShape()
{
	DESTRUCTOR_DEBUG();

}

void QuadShape::Create()
{
	vector<VertexMesh> vertices;
	vertices.resize(4);
	vertices[0] = VertexMesh(-Size.X * 0.5f, -Size.Y * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	vertices[1] = VertexMesh(-Size.X * 0.5f, +Size.Y * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	vertices[2] = VertexMesh(+Size.X * 0.5f, -Size.Y * 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	vertices[3] = VertexMesh(+Size.X * 0.5f, +Size.Y * 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);

	vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };

	SetVertices(vertices, indices);
}

void QuadShape::GUIRender()
{
	SUPER::GUIRender();
}
