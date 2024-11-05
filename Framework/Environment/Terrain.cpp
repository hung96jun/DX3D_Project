#include "Libraries.h"
#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(const UINT Width, const UINT Height, const wstring ImageFile, const wstring ShaderFile)
	:Width(Width), Height(Height)
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(L"TextureShader");
	PShader = ShaderManager::Get()->AddPS(L"TextureShader");

	Vertices.resize(Width * Height);

	float width, height;
	width = (float)Width;
	height = (float)Height;

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

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexUV), (UINT)Vertices.size());
	IBuffer = new IndexBuffer(Indices.data(), (UINT)Indices.size());
	WBuffer = new MatrixBuffer();

	//BaseMap = Texture::Add(ImageFile);
	Mat = new Material();
	Mat->SetDiffuseMap(ImageFile);
	Mat->SetSpecularMap(ImageFile);
	Mat->SetNormalMap(ImageFile);

	Transform.Update();
}

Terrain::~Terrain()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void Terrain::Render()
{
	//BaseMap->PSSet(0);
	Mat->Set();

	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void Terrain::GUIRender()
{
}
