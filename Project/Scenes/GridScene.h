#pragma once

class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	void Disable() override;
	void Render() override;
	void GUIRender() override;

	void Initialize() override {}
	void Update() override {}
	void Destory() override {}
	void PreRender() override {}
	void PostRender() override {}
	void UIRender() override {}
	void ResizeScreen() override {}

private:
	UINT Width = 125, Height = 125;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	MatrixBuffer* WBuffer;

	VertexShader* VShader;
	PixelShader* PShader;

	vector<Vertex> Vertices;
	vector<UINT> Indices;

	Transformation Transform;

	int VertexStart = 0;
};

