#pragma once
class TerrainTestScene : public Scene
{
public:
	TerrainTestScene();
	~TerrainTestScene();

	void Initialize() override;
	void Disable() override {};
	void Destory() override;

	void Update() override;

	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

	void UIRender() override {}
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	vector<VertexUV> Vertices;
	vector<int> Indices;

	Vector3 Pos, Rot, Scale;

	VertexShader* VShader;
	PixelShader* PShader;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	MatrixBuffer* WBuffer;

	Texture* BaseMap;

	Transformation Transform;

	UINT Width, Height;
};

