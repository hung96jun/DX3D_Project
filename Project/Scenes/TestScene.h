#pragma once

class Object;
class Grid;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

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
	//Object* TestObject = nullptr;
	//Grid* TestObject = nullptr;

	vector<VertexTexture> Vertices;
	vector<int> Indices;

	Vector3 Pos, Rot, Scale;

	VertexShader* VShader;
	PixelShader* PShader;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	MatrixBuffer* WBuffer;

	Texture* DiffuseMap = nullptr;

	Matrix World;

	float Color[3] = { 0.5, 0.0, 0.0 };

	vector<Float4> Colors;
};

