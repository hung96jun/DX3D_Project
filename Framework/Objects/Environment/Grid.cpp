#include "Grid.h"

Grid::Grid(const UINT Width, const UINT Height)
	:Object(L"GridShader"), Width(Width), Height(Height)
{
	Vertices.resize((Width + 1) * (Height+ 1));

	for (UINT y = 0; y <= Height; y++)
	{
		for (UINT x = 0; x <= Width; x++)
		{
			UINT index = (Width + 1) * y + x;
			Vertices[index].Position.X = static_cast<float>(x);
			Vertices[index].Position.Y = 0.0f;
			Vertices[index].Position.Z = static_cast<float>(y);
		}
	}

	Indices.resize((Width * Height * 6));
	
	UINT index = 0;
	for (UINT y = 0; y < Height; y++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			Indices[index + 0] = (Width + 1) * y + x;
			Indices[index + 1] = (Width + 1) * (y + 1) + x;
			Indices[index + 2] = (Width + 1) * y + x + 1;
			Indices[index + 3] = (Width + 1) * y + x + 1;
			Indices[index + 4] = (Width + 1) * (y + 1) + x;
			Indices[index + 5] = (Width + 1) * (y + 1) + x + 1;

			index += 6;
		}
	}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), sizeof(Indices.size()));
	WBuffer = new MatrixBuffer();
}

Grid::~Grid()
{
	SAFE_DELETE(WBuffer);
}

void Grid::Render()
{
	VBuffer->Set();
	IBuffer->Set();
	WBuffer->SetVS(0);

	SUPER::Render();
}

void Grid::GUIRender()
{
	SUPER::GUIRender();

}
