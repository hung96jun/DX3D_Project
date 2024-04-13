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
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	//Object* TestObject = nullptr;
	//Grid* TestObject = nullptr;

	vector<VertexColor> Vertices;
	vector<int> Indices;

	Vector3 Pos, Rot, Scale;

	VertexShader* VShader;
	PixelShader* PShader;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	MatrixBuffer* WBuffer;
};

