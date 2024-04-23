#pragma once

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

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
	VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;

	vector<VertexColor> Vertices;
	ID3D11Buffer* VBuffer;

	vector<UINT> Indices;
	ID3D11Buffer* IBuffer;

	Texture* Tex = nullptr;

	Vector3 Pos, Scale;

	Matrix World;
	MatrixBuffer* WBuffer;
};

