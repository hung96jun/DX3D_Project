#pragma once

class Terrain
{
public:
	Terrain(const UINT Width = 256, const UINT Height = 256, const wstring ImageFile = L"Color/White.png", const wstring ShaderFile = L"TextureShader");
	~Terrain();

	void Render();
	void GUIRender();

	Material* GetMaterial() { return Mat; }
	Transformation& GetTransform() { return Transform; }

private:
	VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;

	UINT Width, Height;

	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;
	MatrixBuffer* WBuffer = nullptr;

	vector<VertexUV> Vertices;
	vector<UINT> Indices;

	Transformation Transform;

	//Texture* BaseMap = nullptr;
	Material* Mat = nullptr;
};