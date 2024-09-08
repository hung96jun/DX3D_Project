#include "stdafx.h"
#include "TerrainTestScene.h"

TerrainTestScene::TerrainTestScene()
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(L"TextureShader");
	PShader = ShaderManager::Get()->AddPS(L"TextureShader");

	Width = Height = 256;

	//Vertices.resize(9);
	//Vertices[0].Position = Vector3(0.0f, -3.0f, 0.0f);
	//Vertices[1].Position = Vector3(1.0f, -3.0f, 0.0f);
	//Vertices[2].Position = Vector3(2.0f, -3.0f, 0.0f);

	//Vertices[3].Position = Vector3(0.0f, -3.0f, 1.0f);
	//Vertices[4].Position = Vector3(1.0f, -3.0f, 1.0f);
	//Vertices[5].Position = Vector3(2.0f, -3.0f, 1.0f);

	//Vertices[6].Position = Vector3(0.0f, -3.0f, 2.0f);
	//Vertices[7].Position = Vector3(1.0f, -3.0f, 2.0f);
	//Vertices[8].Position = Vector3(2.0f, -3.0f, 2.0f);
	////Vertices[9].Position = Vector3(0.0f, 0.0f, 1.0f);
	////Vertices[10].Position = Vector3(1.0f, 0.0f, 0.0f);
	////Vertices[11].Position = Vector3(1.0f, 0.0f, 1.0f);

	//Vertices[0].Uv = Vector2(0.0f, 0.0f);
	//Vertices[1].Uv = Vector2(0.5f, 0.0f);
	//Vertices[2].Uv = Vector2(1.0f, 0.0f);
	//Vertices[3].Uv = Vector2(0.0f, 0.5f);
	//Vertices[4].Uv = Vector2(0.5f, 0.5f);
	//Vertices[5].Uv = Vector2(1.0f, 0.5f);
	//Vertices[6].Uv = Vector2(0.0f, 1.0f);
	//Vertices[7].Uv = Vector2(0.5f, 1.0f);
	//Vertices[8].Uv = Vector2(1.0f, 1.0f);

	//Indices = { 
	//	0, 3, 1, 1, 3, 4, 
	//	1, 4, 2, 2, 4, 5,
	//	3, 6, 4, 4, 6, 7, 
	//	4, 7, 5, 5, 7, 8
	//};

	Vertices.resize(Width * Height);

	float width, height;
	width = static_cast<float>(Width);
	height = static_cast<float>(Height);

	for (UINT y = 0; y < Height; y++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			Vector3 pos = Vector3(0.0f);
			pos.X = static_cast<float>(x);
			//pos.Y <- HeightMap
			pos.Y = 0.0f;
			pos.Z = static_cast<float>(y);

			Vector2 uv;
			uv.X = (static_cast<float>(x) / (width - 1.0f));
			uv.Y = (static_cast<float>(y) / (height - 1.0f));

			Vertices[(y * Width) + x].Position = pos;
			Vertices[(y * Width) + x].Uv = uv;
		}
	}

	Indices.resize((Width - 1) * (Height - 1) * 6);
	UINT index = 0;

	for (UINT y = 0; y < Height - 1; y++)
	{
		for (UINT x = 0; x < Width - 1; x++)
		{
			Indices[index + 0] = (y * Width) + x;
			Indices[index + 1] = ((y + 1) * Width) + x;
			Indices[index + 2] = (y * Width) + x + 1;
			Indices[index + 3] = (y * Width) + x + 1;
			Indices[index + 4] = ((y + 1) * Width) + x;
			Indices[index + 5] = ((y + 1) * Width) + x + 1;

			index += 6;
		}
	}

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexUV), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));
	WBuffer = new MatrixBuffer();

	BaseMap = Texture::Add(L"Block/Dirt.png");

	//Transform.SetPosition(Vector3(0.0f));
	//Transform.SetRotation(Vector3(0.0f));
	//Transform.SetScale(Vector3(1.0f));

	Transform.Update();
}

TerrainTestScene::~TerrainTestScene()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void TerrainTestScene::Initialize()
{
}

void TerrainTestScene::Destroy()
{
}

void TerrainTestScene::Update()
{
}

void TerrainTestScene::Render()
{
	BaseMap->PSSet(0);

	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void TerrainTestScene::GUIRender()
{
}
