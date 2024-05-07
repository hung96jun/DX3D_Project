#include "Grid.h"

Grid::Grid(const UINT Width, const UINT Height)
	:Object(L"SimpleShader"), Width(Width), Height(Height)
{
	CONSTRUCTOR_DEBUG();

	Vertices.clear();
	Vertices.resize((Width + 1) * (Height+ 1));

	for (UINT y = 0; y <= Height; y++)
	{
		for (UINT x = 0; x <= Width; x++)
		{
			UINT index = (Width + 1) * y + x;
			Vertices[index].Position.x = static_cast<float>(x);
			Vertices[index].Position.y = 0.0f;
			Vertices[index].Position.z = static_cast<float>(y);

			Vertices[index].Color = Float4(0.2f, 0.2f, 0.2f, 1.0f);
		}
	}

	Indices.clear();
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
	Transform.Update();
}

Grid::~Grid()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void Grid::Render()
{
	//VBuffer->Set();
	//IBuffer->Set();
	//WBuffer->SetVS(0);

	SUPER::Render();
}

void Grid::GUIRender()
{
	SUPER::GUIRender();

	Transform.GUIRender();
}
